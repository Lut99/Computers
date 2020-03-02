/* CHAOS MAKE.cpp
 *   by Lut99
 *
 * Created:
 *   3/1/2020, 11:37:07 AM
 * Last edited:
 *   3/2/2020, 1:11:42 PM
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

extern "C" {
#include "lib/include/InstrBase.h"
}
#include "parser/output/AssemblyParser.tab.h"
#include "lib/include/Globals.h"

#include "lib/include/Version.hpp"
#include "lib/include/cxxopts.hpp"

using namespace cxxopts;
using namespace std;
using namespace Tools;


extern "C" FILE* yyin;

// Define the parse and the make functions
typedef struct instr_list* (*parse_func_t)(const char*);
typedef char* (*compile_func_t)(struct instr*);
__attribute__((unused)) static parse_func_t parse_func;
__attribute__((unused)) static compile_func_t compile_func;

/* Loads the two instruction-set dependend functions from given lang_dir, edition and version */
void* load_instruction_set(string lang_dir, string edition, Version& version) {
    // First, construct the filename
    stringstream sstr;
    sstr << lang_dir;
    sstr << edition;
    sstr << "_";
    string v = to_string(version);
    for (int i = 0; i < v.size(); i++) {
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
        cerr << endl << "ERROR: Could not open library \"" << filename << "\"" << endl << endl;
        exit(-1);
    }

    // Next, try to load the functions
    parse_func = (parse_func_t) dlsym(handle, "parse");
    if (parse_func == NULL) {
        dlclose(handle);
        cerr << endl << "ERROR: Could not load function \"parse\" from library \"" << filename << "\":" << dlerror() << endl << endl;
        exit(-1);
    }
    compile_func = (compile_func_t) dlsym(handle, "compile");
    if (compile_func == NULL) {
        dlclose(handle);
        cerr << endl << "ERROR: Could not load function \"compile\" from library \"" << filename << "\":" << dlerror() << endl << endl;
        exit(-1);
    }

    return handle;
}

/* Writes given list of instructions to target binary file. */
void write_binary(string output_file, struct instr_list* list) {
    ofstream out(output_file, ostream::binary);
    if (!out.is_open()) {
        cerr << endl << "ERROR: Could not open file \"" + output_file + "\": " << strerror(errno) << endl << endl;
        exit(-1);
    }

    // Loop and write
    for (unsigned long i = 0; i < list->len; i++) {
        char* exec = compile_func(list->items[i]);
        out << exec;
        free(exec);
    }

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

    // Let it parse
    struct instr_list* program = parse_func(input.c_str());

    // Write the list to a file
    write_binary(output, program);

    // Free the instructions list
    FREE_INSTR_LIST(program);

    // Close the handle
    dlclose(dl_handle);

    return 0;
}
