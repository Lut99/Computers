/* CHAOSCOMPILER.cpp
*    by Lut99
*
*  This is the compiler for Chaos Assembly.
*  To run, at least three arguments have to be specified (by flag):
*    -s, --src: the path to the source file to compile
*    -o, --out: the path to the assembly file to compile
*    -i, --instr: the id for the instruction set to use.
*  Additional options are:
*  
**/

#include <fstream>
#include <sstream>
#include <iostream>
#include <dlfcn.h>
#include <cerrno>
#include <cstring>
#include <pthread.h>

#include "AssemblyCompiler.h"

#define INPUT_BUFFER_SIZE 256
#define OUTPUT_BUFFER_SIZE 256

using namespace std;
using namespace Compiler;
using namespace DataTypes;

/* Keeps track of the dlopen file handle */
void *compiler_handle;
/* Used to signal the threads they are done */
bool compile_done;

/* Keeps track of given arguments */
struct Settings {
    string source_path;
    string output_path;
    string instruction_set_id;
    bool keep_prepend;
    bool verbose = false;
};

/* Argument struct for pipeline 1. */
struct Pipeline1_Args {
    pthread_t id;
    fstream *preprocessed_stream;
    string *buffer;
};
/* PIPELINE 1: This thread reads the preparsed file line-by-line and outputs those in a buffer */
void* pipeline_in(void *args) {
    Pipeline1_Args *p_args = (Pipeline1_Args*) args;
    
    fstream *pre = p_args->preprocessed_stream;
    string *buff = p_args->buffer;


}

/* Argument struct for pipeline 2. */
struct Pipeline2_Args {
    pthread_t id;
    string *buffer_in;
    char **buffer_out;
    AssemblyCompiler *compiler;
};
/* PIPELINE 2: This thread receives a line from pipeline_in, and outputs the compiled binary to pipeline_out (main thread). */
void* pipeline_compile(void *args) {
    Pipeline2_Args *p_args = (Pipeline2_Args*) args;
    
    string *bin = p_args->buffer_in;
    char **bout = p_args->buffer_out;
    AssemblyCompiler *compiler = p_args->compiler;

}

/* Parses the arguments into a Settings struct. */
void parse_arguments(Settings& result, int argc, char **argv) {
    // First, parse the arguments
    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        if (arg[0] == '-') {
            // Command: do something special
            if (arg == "-s" || arg == "--src") {
                // Check if there is at least one other argument
                if (i == argc - 1) {
                    cerr << "Must specify path after '" << arg << "'" << endl;
                    exit(1);
                }
                // Store the next argument as source file
                result.source_path = argv[i + 1];
                i++;
            } else if (arg == "-o" || arg == "--out") {
                // Check if there is at least one other argument
                if (i == argc - 1) {
                    cerr << "Must specify path after '" << arg << "'" << endl;
                    exit(1);
                }
                // Store the next argument as source file
                result.output_path = argv[i + 1];
                i++;
            } else if (arg == "-i" || arg == "--instr") {
                // Check if there is at least one other argument
                if (i == argc - 1) {
                    cerr << "Must specify path after '" << arg << "'" << endl;
                    exit(1);
                }
                // Store the next argument as source file
                result.instruction_set_id = argv[i + 1];
                i++;
            } else if (arg == "-v" || arg == "--verbose") {
                result.verbose = true;    
            } else if (arg == "--keep-prepend") {
                result.keep_prepend = true;  
            } else {
                cerr << "Unknown option '" << arg << "'" << endl;
                exit(1);
            }
        } else {
            // Normal argument
            // Nothing as of yet
        }
    }

    // Check if any mandatory option is omitted
    if (result.source_path.empty()) {
        cerr << "Must specify an input source file using '-s' or '--src'" << endl;
        exit(1);
    }
    if (result.output_path.empty()) {
        cerr << "Must specify an output binary file using '-o' or '--out'" << endl;
        exit(1);
    }
    if (result.instruction_set_id.empty()) {
        cerr << "Must specify an instruction set file using '-i' or '--instr'" << endl;
        exit(1);
    }
}

/* Removes the last file of a path (e.g., '/users/tim/test' becomes '/users/tim') */
string remove_last_file(string path) {
    // Return if nothing there
    if (path.empty()) {
        return "";
    }

    // First, make sure the last character isn't '/'
    if (path[path.length() - 1] == '/') {
        // Remove it
        path = path.substr(0, path.length() - 1);
    }

    // Don't add anything until the last character has been found
    string to_return = "";
    stringstream sstr;
    for (int i = 0; i < path.length(); i++) {
        char c = path[i];
        sstr << c;
        if (c == '/') {
            // Add the sstr to the to_return and clear the stringstream
            to_return += sstr.str();
            sstr.str("");
            sstr.clear();
        }
    }
    // By not adding the last stringstream, we have removed the last '/'
    return to_return;
}

/* Loads a compiler from a .so file */
AssemblyCompiler *load_compiler(Settings settings, string file_path) {
    // Create the to-be-loaded path by removing the chaos_make file from the
    //   path name (last bit after /) and adding "languages/<compiler id>.so"
    string load_path = file_path;
    load_path = remove_last_file(load_path);
    load_path += "languages/" + settings.instruction_set_id + ".so";

    // Now, try to load the correct instruction set
    compiler_handle = dlopen(load_path.c_str(), RTLD_LAZY);
    if (!compiler_handle) {
        cerr << "Error while loading compiler \"" << settings.instruction_set_id << "\":" << endl << dlerror() << endl;
        return NULL;
    }

    // If success, load the factory
    typedef AssemblyCompiler* (*compiler_factory_p)();
    compiler_factory_p compiler_factory = (compiler_factory_p) dlsym(compiler_handle, "_ZN8Compiler16compiler_factoryEv");
    if (!compiler_factory) {
        cerr << "Could not load compiler factory: " << dlerror() << endl;
        dlclose(compiler_handle);
        return NULL;
    }

    // Finally, create the pointer
    return compiler_factory();
}

/* Opens all file handles in a protective way, i.e., upon failing, closes all opened handles so-far. */
void open_file_handles(ifstream& src, fstream& pre, ofstream& out, Settings settings) {
    // Open the source as input file
    src.open(settings.source_path);
    if (!src.is_open()) {
        cerr << "Failed to open source file \"" << settings.source_path << "\":" << endl << strerror(errno) << endl;
        dlclose(compiler_handle);
        exit(1);
    }
    // Open the preprocess file as both read and write
    pre.open(settings.source_path + "-preprocess", ios::in | ios::out | ios::trunc);
    if (!pre.is_open()) {
        cerr << "Failed to open preprocess file \"" << settings.source_path << "-preprocess" << "\":" << endl << strerror(errno) << endl;
        src.close();
        dlclose(compiler_handle);
        exit(1);
    }
    // Open the output file as write file
    out.open(settings.output_path, ios::out | ios::trunc);
    if (!out.is_open()) {
        cerr << "Failed to open output file \"" << settings.output_path << "\":" << endl << strerror(errno) << endl;
        src.close();
        pre.close();
        dlclose(compiler_handle);
        exit(1);
    }
    // Success
}

/* Preprocesses the input file. Returns true or false whether success has been achieved. */
bool preprocess(ifstream& src, fstream& pre) {
    string line;
    bool multiline_comment = false;
    while (getline(src, line)) {
        // Loop through the line and filter out empty lines, redundant spaces and comments
        int line_length_1 = line.length() - 1;
        char last_char = '\0';
        int in_stream = 0;
        bool add_space = false;
        for (int i = 0; i < line.length(); i++) {
            char c = line[i];

            // Check if multiline comments are activated
            if (multiline_comment) {
                // Only listen for '*/'
                if (i < line_length_1 && c == '*' && line[i + 1] == '/') {
                    // End of multiline comment (skip one char)
                    multiline_comment = false;
                    i++;
                }
            } else {
                // Check if a multiline or singleline comment is starting
                if (i < line_length_1 && c == '/' && line[i + 1] == '*') {
                    // Start of multiline comment (skip one char)
                    multiline_comment = true;
                    i++;
                } else if (i < line_length_1 && c == '/' && line[i + 1] == '/') {
                    // Single line comment: stop immediately with parsing, as this line will be commented anyway
                    break;
                } else if (c == ' ') {
                    add_space = true;
                } else {
                    // Add a space if needed
                    if (add_space) {
                        pre << ' ';
                        add_space = false;
                    }
                    // Add this char to the output stream
                    pre << c;
                    // Keep track of how many and what we added
                    last_char = c;
                    in_stream++;
                }
            }
        }
        // Add a newline IF things have been added
        if (in_stream > 0) {
            pre << endl;
        }
    }
    // Success
    return true;
}

int main(int argc, char **argv) {
    Settings settings;
    parse_arguments(settings, argc, argv);

    // Fetch the compiler
    AssemblyCompiler *compiler = load_compiler(settings, argv[0]);

    // Get handles to both files
    ifstream src;
    fstream pre;
    ofstream out;
    open_file_handles(src, pre, out, settings);

    // Now, preprocess the input file
    if (!preprocess(src, pre)) {
        src.close();
        pre.close();
        out.close();
        dlclose(compiler_handle);
        exit(1);
    }
    // We're done with the source, so close that one in any case
    src.close();

    // Prepare the buffers for the pipelines
    string *input_buffer = new string[INPUT_BUFFER_SIZE];
    char **output_buffer = new char*[OUTPUT_BUFFER_SIZE];

    /* Launch the first pipeline. */
    Pipeline1_Args args_1;
    args_1.preprocessed_stream = &pre;
    args_1.buffer = input_buffer;
    pthread_create(&args_1.id, NULL, pipeline_in, (void*) &args_1);

    /* Launch the second pipeline. */
    Pipeline2_Args args_2;
    args_2.buffer_in = input_buffer;
    args_2.buffer_out = output_buffer;
    args_2.compiler = compiler;
    pthread_create(&args_2.id, NULL, pipeline_compile, (void*) &args_2);

    /* Launch the third pipeline (locally). */
    

    // Done, close the handles
    pre.close();
    out.close();
    dlclose(compiler_handle);
}