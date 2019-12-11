/* CHAOS v1.0 INSTRUCTION SET COMPILER
*    by Lut99
*
*  A subfile for ChaosCompiler, that can compile a given instruction to binary
*  code.
**/

#include <iostream>
#include <sstream>

#include "Chaos1_0.h"

using namespace std;

string *resize(string *to_resize, int old_size, int new_size) {
    string *resized = new string[new_size];
    for (int i = 0; i < old_size; i++) {
        resized[i] = to_resize[i];
    }
    delete[] to_resize;
    return resized;
}

int string_split(string to_split, string **result, char delimiter = ' ') {
    string *list = new string[0];
    int parts = 0;
    stringstream part;
    int in_stream = 0;
    for (int i = 0; i < to_split.length(); i++) {
        if (to_split[i] == delimiter) {
            // Resize to one bigger and put the stream in it
            list = resize(list, parts, parts + 1);
            list[parts] = part.str();
            parts++;
            // Reset the stream
            part.str("");
            part.clear();
            in_stream = 0;
        } else {
            part << to_split[i];
            in_stream++;
        }
    }
    // If there is any part left, resize and add
    if (in_stream > 0) {
        // Resize to one bigger and put the stream in it
        list = resize(list, parts, parts + 1);
        list[parts] = part.str();
        parts++;
    }
    // Return
    (*result) = list;
    return parts;
}

void Compiler::Chaos::parse_chaos_1_0_0(ifstream& src, ofstream& bin, bool verbose) {
    // Loop through all the lines in the preprocessed file
    string line;
    for (int i_line = 0; getline(src, line); i_line++) {
        /* Step 1: Get all words */
        string *words;
        int n_words = string_split(line, &words);

        // Check the command
        string command = words[0];
        if (command == "ADD") {
            // Check if there are enough arguments
            if (n_words != 3) {
                cerr << "Line " << i_line << ": 'ADD' instruction requires 2 arguments, got " << (n_words - 1) << endl;
                exit(1);
            }
            // Throw it through the parser
        } else if (command == "REG_SET") {
            // Check if there are enough arguments
            if (n_words != 3) {
                cerr << "Line " << i_line << ": 'REG_SET' instruction requires 2 arguments, got " << (n_words - 1) << endl;
                exit(1);
            }
            // Throw it through the parser
        } else if (command == "OUT") {
            // Check if there are enough arguments
            if (n_words != 2) {
                cerr << "Line " << i_line << ": 'OUT' instruction requires 1 argument, got " << (n_words - 1) << endl;
                exit(1);
            }
            // Throw it through the parser
        } else if (command == "END") {
            // Check if there are enough arguments
            if (n_words != 1) {
                cerr << "Line " << i_line << ": 'END' instruction requires no arguments, got " << (n_words - 1) << endl;
                exit(1);
            }
            // Throw it through the parser
        } else {
            delete[] words;
            cerr << "Line " << i_line << ": Unknown instruction \"" << command << "\"" << endl;
            exit(1);
        }
        delete[] words;
    }
}