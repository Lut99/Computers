/* CHAOS MAKE.cpp
 *   by Lut99
 *
 * Created:
 *   3/1/2020, 11:37:07 AM
 * Last edited:
 *   3/4/2020, 8:21:26 PM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   The chaos_make is the entry function for the Assembly compiler of the
 *   Chaos Instruction set. It makes use of flex and bison to parse the
 *   file. Which version or edition of Chaos to make can be specified on
 *   the command line.
**/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <dlfcn.h>
#include <cstring>
#include <cerrno>

#include "lib/include/Version.hpp"
#include "lib/include/cxxopts.hpp"

using namespace cxxopts;
using namespace std;
using namespace Tools;


// Define the parse and the make functions
typedef void (*compile_func_t)();
typedef void (*set_file_func_t)(FILE*);
compile_func_t compile_func;
set_file_func_t set_yyin;
set_file_func_t set_out;

/* Loads the two instruction-set dependend functions from given lang_dir, edition and version */
void* load_instruction_set(string lang_dir, string edition, Version& version) {
    // First, construct the filename
    stringstream sstr;
    sstr << lang_dir;
    sstr << edition;
    sstr << "_";
    string v = to_string(version);
    for (size_t i = 0; i < v.size(); i++) {
        if (v[i] == '.') {
            v[i] = '_';
        }
    }
    sstr << v;
    sstr << ".so";
    string filename = sstr.str();
    
    // Try to open the library
    void* handle = dlopen(filename.c_str(), RTLD_NOW);
    if (handle == NULL) {
        cerr << endl << "ERROR: failed to load library: " << dlerror() << endl << endl;
        exit(-1);
    }

    // Next, try to load the functions
    compile_func = (compile_func_t) dlsym(handle, "yyparse");
    if (compile_func == NULL) {
        dlclose(handle);
        cerr << endl << "ERROR: failed to load compile_func: " << filename << "\":" << dlerror() << endl << endl;
        exit(-1);
    }
    set_yyin = (set_file_func_t) dlsym(handle, "set_yyin");
    if (set_yyin == NULL) {
        dlclose(handle);
        cerr << endl << "ERROR: failed to load set_yyin: " << filename << "\":" << dlerror() << endl << endl;
        exit(-1);
    }
    set_out = (set_file_func_t) dlsym(handle, "set_out");
    if (set_out == NULL) {
        dlclose(handle);
        cerr << endl << "ERROR: failed to load set_out: " << filename << "\":" << dlerror() << endl << endl;
        exit(-1);
    };

    return handle;
}

/* Writes given list of instructions to target binary file. */
void write_binary(string output_file, char* program) {
    ofstream out(output_file, ostream::binary);
    if (!out.is_open()) {
        cerr << endl << "ERROR: Could not open file \"" + output_file + "\": " << strerror(errno) << endl << endl;
        exit(-1);
    }

    // Write the program
    out << program;

    // Close the file
    out.close();
}

int main(int argc, char** argv) {
    // Init the option variables
    string edition, input, output, lang_dir;
    bool verbose;
    Version version(0, 0, 0);

    // Parse the options
    Options arguments("chaos_make", "Compiles Chaos Assembly to the binary equivalent for a Chaos Instruction Set.");
    arguments.add_options()
        ("E,edition", "The string identifier of the Chaos edition that needs to be compiled. Default is the general purpose desktop branch.", value<string>())
        ("V,version", "The string identifier of the Chaos version of the selected edition that needs to be compiled. Default is the most recent.", value<Version>())
        ("i,input", "The name of the input file.", value<string>())
        ("o,output", "The name of the output file (default: 'output.cex').", value<string>())
        ("l,lang_dir", "Directory where all binaries for each language is located (default: 'bin/linux/lang/').", value<string>())
        ("v,verbose", "If given, prints debug texts.")
        ;
    arguments.parse_positional("input");

    auto result = arguments.parse(argc, argv);
    
    // Parse the edition and version
    try {
        edition = result["edition"].as<string>();
    } catch (domain_error& opt) {
        edition = "main";
    } catch (OptionParseException& opt) {
        cerr << "Could not parse edition: " << opt.what() << endl;
        exit(-1);
    }
    try {
        version = result["version"].as<Version>();
    } catch (domain_error& opt) {
        version = Version(1, 0, 0);
    } catch (OptionParseException& opt) {
        cerr << "Could not parse version: " << opt.what() << endl;
        exit(-1);
    }

    // Parse the input and the output
    try {
        input = result["input"].as<string>();
    } catch (OptionParseException& opt) {
        cerr << "Could not parse input: " << opt.what() << endl;
        exit(-1);
    }
    try {
        output = result["output"].as<string>();
    } catch (domain_error& opt) {
        output = "output.cex";
    } catch (OptionParseException& opt) {
        cerr << "Could not parse output: " << opt.what() << endl;
        exit(-1);
    }
    try {
        lang_dir = result["lang_dir"].as<string>();
    } catch (domain_error& opt) {
        lang_dir = "bin/linux/lang/";
    } catch (OptionParseException& opt) {
        cerr << "Could not parse lang_dir: " << opt.what() << endl;
        exit(-1);
    }
    // Make sure lang_dir ends on a '/'
    if (lang_dir[lang_dir.size() - 1] != '/') {
        lang_dir += '/';
    }

    // Check verbosity
    verbose = result.count("verbose") > 0;

    // First, load the instruction library
    void* dl_handle = load_instruction_set(lang_dir, edition, version);

    // Open the files needed to handle this
    FILE* in = fopen(input.c_str(), "r");
    if (in == NULL) {
        cerr << endl << "ERROR: Could not open file \"" << input << "\": " << strerror(errno) << endl << endl;
        exit(-1);
    }
    FILE* out = fopen(output.c_str(), "w");
    if (out == NULL) {
        fclose(in);
        cerr << endl << "ERROR: Could not open file \"" << output << "\": " << strerror(errno) << endl << endl;
        exit(-1);
    }

    // Run the compiler
    set_yyin(in);
    set_out(out);
    compile_func();

    // Close the files
    fclose(in);
    fclose(out);

    // Close the handle
    dlclose(dl_handle);

    return 0;
}
