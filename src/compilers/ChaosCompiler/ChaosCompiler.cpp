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
#include <strings.h>

#include "Chaos1_0.h"

using namespace std;
using namespace Compiler;


int main(int argc, char **argv) {
    string ARG_SOURCE_FILE = "";
    string ARG_OUTPUT_FILE = "";
    string ARG_INSTR_SET = "";

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
            } else {
                cerr << "Unknown option '" << arg << "'" << endl;
                exit(1);
            }
        } else {
            // Normal argument
            // Nothing as of yet
        }
    }

    // Check if any option is not set
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

    // Open file handles and load prepare the instruction set compiler
    // TBD
}