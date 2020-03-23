/* TEST SCANNER.cpp
 *   by Lut99
 *
 * Created:
 *   3/23/2020, 1:25:15 PM
 * Last edited:
 *   3/23/2020, 1:48:18 PM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   This file is used to test the scanner. It wraps it, then sets its
 *   input as stdin and keeps scanning until EOF is reached.
**/

#include <iostream>
#include <fstream>
#include <string>

#include "ScannerExceptions.hpp"
#include "Scanner.hpp"

using namespace std;
using namespace Assembler;


static string token_strings[] = {
    "set"
};

int main(int argc, char** argv) {
    // Create the Scanner
    istream* in = &cin;
    if (argc == 2) {
        ifstream* file = new ifstream(argv[1]);
        if (!file->is_open()) {
            cerr << "Could not open file \"" << argv[1] << "\": " << strerror(errno) << endl;
            exit(errno);
        }
        in = (istream*) file;
    }

    Scanner scn(*in);

    // Keep scannin'
    while (true) {
        int t;
        try {
            t = scn.getToken();
        } catch(SyntaxError& e) {
            cerr << "Syntax error in line " << e.line << ", col " << e.col << ": \"" << e.text << "\"" << endl;
            exit(-1);
        }

        if (t == -1) { break; }

        // Print the token
        cout << token_strings[t] << endl << endl;
    }

    // Close the file if needed
    if (argc == 2) {
        ((ifstream*) in)->close();
    }
}