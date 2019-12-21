/* CHAOS v1.0 INSTRUCTION SET COMPILER
*    by Lut99
*
*  A subfile for ChaosCompiler, that can compile a given instruction to binary
*  code.
**/

#include <iostream>
#include <sstream>

#include "../support/LinkedList.h"
#include "../support/StringConverter.cpp"
#include "Chaos1_0.h"

using namespace std;

/* INSTRUCTION PARSERS HELPERS */
/* Parses '$regX', '<regX' or '0xXX' syntax. The int returned specifies which of the versions it is (0=register, 1=memory and 2 is constant), and the value integer becomes the register or memory address, respectively, or in the last case the constant value. If -1 is returned, then an error happened, of which the error code is specified in the value variable. */
int tool_reg(string arg, unsigned long& value) {
    // Try to see if it's a memory or register value
    if (arg[0] == '$' || arg[0] == '<') {
        // Try to parse as registry value
        if (arg[1] != 'r' or arg[2] != 'e' or arg[3] != 'g') {
            // Return 'registry syntax error'
            value = -1;
            return -1;
        }

        // Fetch the register number
        char reg;
        try {
            reg = StringConverter::toInteger<char>(arg.substr(4));
        } catch (StringConverter::StringConvertionException& e) {
            // Show as parse error
            cerr << "Invalid register number \"" << arg.substr(4) << "\": Must be an integer ranging 0-15" << endl;
            exit(1);
        }

        // Also throw error if out-of-bounds
        if (reg < 0 || reg > 15) {
            cerr << "Invalid register number \"" << arg.substr(4) << "\": Must be an integer ranging 0-15" << endl;
            exit(1);
        }

        // Cool, now return that as value and mark the appropriate type
        value = (unsigned long) reg;
        if (arg[0] == '$') {
            return 0;
        }
        return 1;
    } else if (argp[0]) {

    }
    // No known format
    cerr << "Unknown register or constant \"" << arg << "\"" << endl;
    exit(1);
}

/* INSTRUCTION PARSERS */
string parse_add(string *args, ofstream& output_file) {
    // Write the binary ADD ID to the file
    output_file << 0x00;
    // Next, parse the instructions
}

Compiler::Chaos::idmap Compiler::Chaos::INSTRUCTION_MAP = {
    {"ADD", parse_add}
};

int string_split(string to_split, string **result, char delimiter = ' ') {
    // Create a list for the stringstreams
    DataTypes::LinkedList<string> list;

    // Iterate over the string and split into multiple stringstreams
    stringstream sstr;
    int in_str = 0;
    for (int i = 0; i < to_split.length(); i++) {
        if (to_split[i] == delimiter) {
            // Append the latest string to the list
            list.append(sstr.str());
            sstr.str("");
            sstr.clear();
            in_str = 0;
        } else {
            // Append to the last stringstream
            sstr << to_split[i];
            in_str++;
        }
    }
    // Add any leftover stringstreams
    if (in_str) {
        list.append(sstr.str());
    }

    // Return the list as array
    (*result) = list.to_array();
    
    // Done
    return list.length();
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