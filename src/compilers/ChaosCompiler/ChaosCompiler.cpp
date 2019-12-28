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

#include <iostream>
#include <fstream>
#include <sstream>
#include <cerrno>
#include <cstring>

#include "AssemblyCompiler.h"

using namespace std;
using namespace Compiler;

struct 

int main(int argc, char **argv) {
    string ARG_SOURCE_FILE = "";
    string ARG_OUTPUT_FILE = "";
    string ARG_INSTR_SET = "";
    bool ARG_KEEP_PREPEND = false;
    bool ARG_VERBOSE = false;
    CompileFunction compiler;
    string compiler_name;

    // First, parse the arguments
    for (int i = 0; i < argc; i++) {
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
                ARG_SOURCE_FILE = argv[i + 1];
                i++;
            } else if (arg == "-o" || arg == "--out") {
                // Check if there is at least one other argument
                if (i == argc - 1) {
                    cerr << "Must specify path after '" << arg << "'" << endl;
                    exit(1);
                }
                // Store the next argument as source file
                ARG_OUTPUT_FILE = argv[i + 1];
                i++;
            } else if (arg == "-i" || arg == "--instr") {
                // Check if there is at least one other argument
                if (i == argc - 1) {
                    cerr << "Must specify path after '" << arg << "'" << endl;
                    exit(1);
                }
                // Store the next argument as source file
                ARG_INSTR_SET = argv[i + 1];
                i++;
            } else if (arg == "-v" || arg == "--verbose") {
                ARG_VERBOSE = true;    
            } else if (arg == "--keep-prepend") {
                ARG_KEEP_PREPEND = true;  
            } else {
                cerr << "Unknown option '" << arg << "'" << endl;
                exit(1);
            }
        } else {
            // Normal argument
            // Nothing as of yet
        }
    }

    // Check if any mandatory option is not set
    if (ARG_SOURCE_FILE.empty()) {
        cerr << "Must specify an input source file using '-s' or '--src'" << endl;
        exit(1);
    }
    if (ARG_OUTPUT_FILE.empty()) {
        cerr << "Must specify an output binary file using '-o' or '--out'" << endl;
        exit(1);
    }
    if (ARG_INSTR_SET.empty()) {
        cerr << "Must specify an instruction set file using '-i' or '--instr'" << endl;
        exit(1);
    }

    if (ARG_VERBOSE) {
        cout << endl << ">> CHAOS ASSEMBLY LANGUAGE COMPILER <<" << endl << endl;
    }

    // Open file handles and prepare the instruction set compiler
    if (ARG_VERBOSE) {
        cout << ">> Opening file handles..." << endl;
    }
    ifstream src(ARG_SOURCE_FILE);
    if (!src.is_open()) {
        cerr << "Could not open file \"" << ARG_SOURCE_FILE << "\": " << strerror(errno) << endl;
        exit(1);
    }
    ofstream bin(ARG_OUTPUT_FILE, ios::out | ios::binary);
    if (!bin.is_open()) {
        // Close the src file again
        src.close();
        cerr << "Could not open file \"" << ARG_OUTPUT_FILE << "\": " << strerror(errno) << endl;
        exit(1);
    }
    if (ARG_VERBOSE) {
        cout << ">> Getting correct compiler..." << endl;
    }

    // Check if it matches an identifier
    if (ARG_INSTR_SET == "1_0_0") {
        // Store the correction function pointer
        compiler = Compiler::Chaos::parse_chaos_1_0_0;
        compiler_name = "Chaos v1.0.0 Assembly Language Compiler";
    } else {
        cerr << "Unknown instruction set ID: \"" << ARG_INSTR_SET << "\"" << endl;
        cerr << "See the wiki (github.com/Lut99/Computers/wiki) for more information." << endl;
        exit(1);
    }
    
    /* STAGE 1: Pre-parse file */
    if (ARG_VERBOSE) {
        cout << ">> Opening write handle to preprocess file..." << endl;
    }
    // Open a new file handle
    ofstream preparsed(ARG_SOURCE_FILE + "-preprocess");
    if (!preparsed.is_open()) {
        // Close other two files
        src.close();
        bin.close();
        cerr << "Could not open file \"" << ARG_SOURCE_FILE << "-preprocess\": " << strerror(errno) << endl;
        exit(1);
    }

    // Loop through the other file line-by-line
    if (ARG_VERBOSE) {
        cout << ">> Preprocessing..." << endl;
    }
    string line;
    bool multiline_comment = false;
    while (getline(src, line)) {
        // Loop character-wise, and be sure to skip comments
        bool line_comment = false;
        int new_chars = 0;
        bool one_space = false;
        for (int i = 0; i < line.length(); i++) {
            char c = line[i];
            if (multiline_comment) {
                // Check for when it ends
                if (i < line.length() - 1 && c == '*' && line[i + 1] == '/') {
                    // We stopped, also skip other of comment line
                    multiline_comment = false;
                    i++;
                }
            } else {
                // Check for when either comment starts
                if (i < line.length() - 1 && c == '/' && line[i + 1] == '*') {
                    // Begin multiline, also skip the other of two comment chars
                    multiline_comment = true;
                    i++;
                } else if (i < line.length() - 1 && c == '/' && line[i + 1] == '/') {
                    // Single line: skip rest of line
                    break;
                } else {
                    // No comments
                    // If previous character was a space, skip this one
                    if (c != ' ' || (!one_space && i < line.length() - 1)) {
                        if (c != ' ') {
                            one_space = false;
                        } else {
                            one_space = true;
                        }
                        preparsed << c;
                        new_chars++;
                    }
                }
            }
        }
        // Add a newline if required
        if (new_chars > 0) {
            preparsed << endl;
        }
    }
    if (ARG_VERBOSE) {
        cout << ">> Done preprocessing, closing file handles..." << endl;
    }
    // Done
    src.close();
    preparsed.close();

    if (ARG_VERBOSE) {
        cout << ">> Re-opening preprocess file for reading..." << endl;
    }

    // STAGE 2: RUN THE COMPILER
    ifstream preparsed_in(ARG_SOURCE_FILE + "-preprocess");
    if (!preparsed_in.is_open()) {
        // Close other two files
        src.close();
        bin.close();
        cerr << "Could not open file \"" << ARG_SOURCE_FILE << "-preprocess\": " << strerror(errno) << endl;
        exit(1);
    }

    if (ARG_VERBOSE) {
        cout << ">> Compiling using '" << compiler_name << "'..." << endl;
    }

    compiler(preparsed_in, bin, ARG_VERBOSE);

    if (ARG_VERBOSE) {
        cout << ">> Done." << endl;
        cout << ">> Closing handles..." << endl;
    }

    // Done; close all files
    preparsed_in.close();
    bin.close();

    // Remove the preparsed file
    if (!ARG_KEEP_PREPEND) {
        if (ARG_VERBOSE) {
            cout << ">> Removing preprocess file..." << endl;
        }

        if (remove((ARG_SOURCE_FILE + "-preprocess").c_str()) != 0) {
            cerr << "Could not remove file \"" << ARG_SOURCE_FILE << "-preprocess\": " << strerror(errno) << endl;
            exit(1);
        }
    } else if (ARG_VERBOSE) {
        cout << ">> Keep preprocess file flag given, skipping removal" << endl;
    }

    cout << "Done." << endl;
}