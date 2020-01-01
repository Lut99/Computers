/* CHAOS v1.0 INSTRUCTION SET COMPILER
*    by Lut99
*
*  A subfile for ChaosCompiler, that can compile a given instruction to binary
*  code.
**/

#include <iostream>
#include <sstream>
#include <string>

#include "../../../../lib/LinkedList.cpp"
#include "Chaos1_0_0.h"

using namespace std;
using namespace Compiler;
using namespace DataTypes;

/* TOOLS */

/* Splits a given string into multiple words. The given characters is the split char, and defaults to ' '. The result is allocated, and should be deallocated later on. */
string* split(string text, char splitter = ' ') {
    // Create a linkedlist for the word parts
    LinkedList<string> words;

    stringstream sstr;
    for (int i = 0; i < text.length(); i++) {
        char c = text[i];
        if (c == splitter) {
            // Add the string value to the linkedlist
            words.append(sstr.str());
            // Clear the stringstream
            sstr.str("");
            sstr.clear();
        } else {
            // Add to the sstr
            sstr << c;
        }
    }

    // Add the remaining sstr
    words.append(sstr.str());

    // Return the alocated buffer
    return words.to_array();
}



Chaos1_0_0_compiler::Chaos1_0_0_compiler()
    : AssemblyCompiler("Chaos Assembly Language v1.0.0 Compiler", "Chaos1_0_0")
{}

void Chaos1_0_0_compiler::compile(DataTypes::BinaryStream& result, std::string line) {
    // First: we split each word, and assign the first to be the command
    string *words = split(line);
    string command = words[0];
    string *args = words + 1;

    // Determine the proper compile function for that command
    if (command == "add") {
        
    } else {
        cerr << "Parse error: unknown command \"" << command << "\"" << endl;
        delete[] words;
        exit(1);
    }
}

AssemblyCompiler *Compiler::compiler_factory() {
    return new Chaos1_0_0_compiler;
}
