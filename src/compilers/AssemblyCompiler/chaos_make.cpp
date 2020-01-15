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
#include <array>

#include "CompilerErrors.h"
#include "../../include/LinkedList.h"
#include "../../include/Buffer.h"
#include "../../include/StringConverter.h"
#include "../../include/Array.h"
#include "AssemblyCompiler.h"

#define INPUT_BUFFER_SIZE 256
#define OUTPUT_BUFFER_SIZE 256
#define FACTORY_SYMBOL "_ZN8Compiler16compiler_factoryENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE"

using namespace std;
using namespace Compiler;
using namespace DataTypes;

/* Returns a string with the hexadecimal representation of given byte array. */
string hexify(char *data, std::size_t size) {
    stringstream sstr;
    sstr << "0x";
    for (std::size_t i = 0; i < size; i++) {
        if (i > 0) {sstr << ' ';}
        unsigned char c = data[i];
        if (c < 10) {sstr << '0';}
        sstr << (int) c;
    }
    return sstr.str();
}

/* Splits given string into an array of string. The splitpoint is a character, which is ' ' by default. Optionally, all characters can also be converted to their lowercase counterpart if desired. */
void split(Array<string>& result, string text, char split_point=' ', bool lowercase=false) {
    LinkedList<string> parts;
    stringstream part;

    for (size_t i = 0; i < text.length(); i++) {
        char c = text[i];

        if (c == split_point) {
            parts.append(part.str());
            part.str("");
            part.clear();
        } else {
            if (lowercase) {
                part << tolower(c);
            } else {
                part << c;
            }
        }
    }

    // Add the last part
    parts.append(part.str());

    // Return a newly allocated array
    parts.to_array(result);
}

/* Keeps track of the dlopen file handle */
void *compiler_handle;
/* Used to signal the fetch step of the pipeline is done */
int fetch_done;
/* Used to signal the compile step of the pipeline is done */
int compile_done;
/* Used to propagate an error through the threads */
bool error_occured;

/* Keeps track of given arguments */
struct Settings {
    string source_path;
    string output_path;
    string instruction_set_id;
    bool keep_prepend;
    bool verbose = false;
};

/* Struct that keeps track of line information */
struct Pipeline_Line {
    std::string command;
    Array<string> args;
    std::size_t number;
};
/* Argument struct for pipeline 1. */
struct Pipeline1_Args {
    pthread_t id;
    string filepath;
    ifstream *preprocessed_stream;
    Buffer<Pipeline_Line> *buffer;
};
/* PIPELINE 1: This thread reads the preparsed file line-by-line and outputs those in a buffer */
void* pipeline_in(void *args) {
    Pipeline1_Args *p_args = (Pipeline1_Args*) args;
    
    ifstream *pre = p_args->preprocessed_stream;
    Buffer<Pipeline_Line> *buff = p_args->buffer;

    // Read line-by-line and, unless they're empty, output them to the next
    //   thread
    string line;
    int done = 0;
    while (getline(*pre, line)) {
        if (!line.empty() && line.length() > 0) {
            // Split the line into words
            Array<string> words;
            split(words, line, true);
            if (words.length() < 2) {
                cerr << "Loading error occured: no line number or instruction in \"" << line << "\"" << endl;
                error_occured = true;
                return NULL;
            }

            // Convert the line number to std::size_t
            std::size_t number;
            try {
                number = StringConverter::toInteger<std::size_t>(words[0]);
            } catch (StringConverter::StringConvertionException& e) {
                // Print it
                cerr << "Loading error occured: " << e.msg << endl;
                error_occured = true;
                return NULL;
            }

            // Split into command and arguments
            string command = words[0];
            Array<string> args;
            words.subset(args, 1);

            // Fill a pipeline struct
            Pipeline_Line p_line;
            p_line.command = words[0];
            p_line.args = words;
            p_line.number = number;

            // Write to buffer
            buff->write(p_line);
            
            cout << "Pipeline #1: Got line " << p_line.number << " \"" << line << "\"" << endl;
            cout.flush();

            // Mark this line as done
            done++;
        }

        // Escape on error
        if (error_occured) {
            return NULL;
        }
    }

    cout << "Pipeline #1, signing off (did " << done << " items)" << endl;
    cout.flush();

    // Propagate done
    fetch_done = done;

    return NULL;
}

/* Argument struct for pipeline 2. */
struct Pipeline2_Args {
    pthread_t id;
    string filepath;
    Buffer<Pipeline_Line> *buffer_in;
    Buffer<BinaryString> *buffer_out;
    AssemblyCompiler *compiler;
};
/* PIPELINE 2: This thread receives a line from pipeline_in, and outputs the compiled binary to pipeline_out (main thread). */
void* pipeline_compile(void *args) {
    Pipeline2_Args *p_args = (Pipeline2_Args*) args;
    
    Buffer<Pipeline_Line> *bin = p_args->buffer_in;
    Buffer<BinaryString> *bout = p_args->buffer_out;
    AssemblyCompiler *compiler = p_args->compiler;

    BinaryStream result;
    int done = 0;
    while (true) {
        // Wait until we can read
        while (!bin->can_read() && !error_occured) {
            // Stop entirely if there is nothing coming anymore
            if (fetch_done == done) {
                cout << "Pipeline #2, going home (did " << done << " items)" << endl;
                cout.flush();
                // Propagate done
                compile_done = done;
                return NULL;
            }
        }
        if (error_occured) {
            // Stop
            return NULL;
        }

        // Read the line
        Pipeline_Line line;
        bin->read(line);

        cout << "Pipeline #2: Got line " << line.number << " \"" << line.command << "\" from #1" << endl;
        cout.flush();

        // Compile it
        try {
            compiler->compile(result, line.command, line.args);
        } catch (ParseException& e) {
            // Show the error
            cerr << "Line " << line.number << ": " << e.name << ": " << e.msg << endl;
            // Stop before anything new is allocated
            error_occured = true;
            return NULL;
        }

        // Fetch the result
        char *b_result = new char[result.length()];
        std::size_t read_size = result.flush(b_result);

        // Create the binarystring
        BinaryString to_write = BinaryString(b_result, read_size, false);

        // Push the data to the next buffer
        while(!bout->write(to_write) && !error_occured) {}
        if (error_occured) {
            return NULL;
        }

        // Mark as done
        done++;
    }
}

/* Argument struct for pipeline 3. */
struct Pipeline3_Args {
    pthread_t id;
    string filepath;
    ofstream *output_stream;
    Buffer<BinaryString> *buffer_out;
};
/* PIPELINE 3: This thread receives compiled binary strings from the second pipeline, and forwards these to the output file. */
void *pipeline_out(void *args) {
    Pipeline3_Args *p_args = (Pipeline3_Args*) args;
    
    ofstream *out = p_args->output_stream;
    Buffer<BinaryString> *buff = p_args->buffer_out;

    // Read from the buffer until it is empty && nothing is coming anymore
    BinaryString res;
    int done = 0;
    while (true) {
        // Wait until we can read
        while (!buff->can_read() && !error_occured) {
            // Stop entirely if there is nothing coming anymore
            if (compile_done == done) {
                cout << "Pipeline #3, sayin' goodbye (did " << done << " items)" << endl;
                cout.flush();
                return NULL;
            }
        }
        if (error_occured) {
            // Stop the thread
            return NULL;
        }

        // Actually read
        buff->read(res);

        cout << "Pipeline #3: Got line \"" << hexify(res.data, res.size) << "\" from #2" << endl;
        cout.flush();

        // Send it to the output
        out->write(res.data, res.size);

        // Clear the res.data
        delete[] res.data;

        // Mark as done
        done++;
    }
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
    compiler_factory_p compiler_factory = (compiler_factory_p) dlsym(compiler_handle, FACTORY_SYMBOL);
    if (!compiler_factory) {
        cerr << "Could not load compiler factory: " << dlerror() << endl;
        dlclose(compiler_handle);
        return NULL;
    }

    // Finally, create the pointer
    return compiler_factory();
}

/* Opens all file handles in a protective way, i.e., upon failing, closes all opened handles so-far. */
void open_file_handles(ifstream& in, string in_path, ofstream& out, string out_path) {
    // Open the source as input file
    in.open(in_path);
    if (!in.is_open()) {
        cerr << "Failed to open source file \"" << in_path << "\":" << endl << strerror(errno) << endl;
        dlclose(compiler_handle);
        exit(1);
    }
    // Open the preprocess file as both read and write
    out.open(out_path, ios::out | ios::trunc);
    if (!out.is_open()) {
        cerr << "Failed to open preprocess file \"" << out_path << "\":" << endl << strerror(errno) << endl;
        in.close();
        dlclose(compiler_handle);
        exit(1);
    }
    // Success
}

/* Preprocesses the input file. Returns true or false whether success has been achieved. */
bool preprocess(ifstream& src, ofstream& pre) {
    string line;
    bool multiline_comment = false;
    std::size_t line_i = 0;
    while (getline(src, line)) {
        // Loop through the line and filter out empty lines, redundant spaces and comments
        int line_length_1 = line.length() - 1;
        char last_char = '\0';
        int in_stream = 0;
        bool add_space = false;
        stringstream sstr;
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
                        sstr << ' ';
                        add_space = false;
                    }
                    // Add this char to the output stream
                    sstr << c;
                    // Keep track of how many and what we added
                    last_char = c;
                    in_stream++;
                }
            }
        }
        // Add things to the output stream IF anything has been added
        if (in_stream > 0) {
            pre << line_i << ' ' << sstr.str() << endl;
        }
        line_i++;
    }
    // Success
    return true;
}

int main(int argc, char **argv) {
    Settings settings;
    parse_arguments(settings, argc, argv);

    // In any case, show a summary
    cout << "chaos_make -s " << settings.source_path << " -o " << settings.output_path << " -i " << settings.instruction_set_id;
    if (settings.verbose) {
        cout << " -v";
    }
    if (settings.keep_prepend) {
        cout << " --keep-prepend";
    }
    cout << endl;

    // Fetch the compiler
    AssemblyCompiler *compiler = load_compiler(settings, argv[0]);

    // Get handles to both files
    ifstream src;
    ofstream pre;
    open_file_handles(src, settings.source_path, pre, settings.source_path + "-preprocess");

    // Now, preprocess the input file
    if (!preprocess(src, pre)) {
        src.close();
        pre.close();
        dlclose(compiler_handle);
        exit(1);
    }
    // We're done with src and pre
    src.close();
    pre.close();

    // Re-open pre as the read and out as the output this time
    ifstream pre_2;
    ofstream out;
    open_file_handles(pre_2, settings.source_path + "-preprocess", out, settings.output_path);

    // Prepare the buffers for the pipelines
    Buffer<Pipeline_Line> *input_buffer = new Buffer<Pipeline_Line>(256);
    Buffer<BinaryString> *output_buffer = new Buffer<BinaryString>(256);

    fetch_done = -1;
    compile_done = -1;
    error_occured = false;

    /* Launch the first pipeline. */
    Pipeline1_Args args_1;
    args_1.filepath = settings.source_path;
    args_1.preprocessed_stream = &pre_2;
    args_1.buffer = input_buffer;
    pthread_create(&args_1.id, NULL, pipeline_in, (void*) &args_1);

    /* Launch the second pipeline. */
    Pipeline2_Args args_2;
    args_2.filepath = settings.source_path;
    args_2.buffer_in = input_buffer;
    args_2.buffer_out = output_buffer;
    args_2.compiler = compiler;
    pthread_create(&args_2.id, NULL, pipeline_compile, (void*) &args_2);

    /* Launch the third pipeline. */
    Pipeline3_Args args_3;
    args_3.filepath = settings.source_path;
    args_3.output_stream = &out;
    args_3.buffer_out = output_buffer;
    pthread_create(&args_3.id, NULL, pipeline_out, (void*) &args_3);

    // Wait until they're all done
    pthread_join(args_1.id, NULL);
    pthread_join(args_2.id, NULL);
    pthread_join(args_3.id, NULL);

    // Deallocate the buffers
    delete input_buffer;
    delete output_buffer;

    // Close the handles
    pre.close();
    out.close();
    dlclose(compiler_handle);
}