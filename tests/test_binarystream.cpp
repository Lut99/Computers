/* TEST BINARYSTREAM.cpp
*    by Lut99
*
*  A test file for the BinaryStream library.
**/

#include <iostream>

#include "../include/BinaryStream.h"

using namespace std;
using namespace DataTypes;

bool test_default() {
    cout << "Testing adding of standard types..." << endl;

    cout << "  Creating BinaryStream..." << endl;
    BinaryStream bstream;
    bstream << 36;
    bstream << (unsigned char) 88;
    bstream << "Hello there!";
    cout << "  Result: \"" << bstream << "\"" << endl;

    // Construct the expected char array
    char expected[16];
    expected[0] = 36;
    expected[1] = 88;
    for (int i = 0; i < 14; i++) {
        expected[i + 2] = "Hello there!"[i];
    }
    // Check if the last one is '\0'
    cout << "  Expected is \\0? " << (expected[14] == '\0') << endl;

    // Check the correctness
    bool correct = false;
    if (bstream.length() == 16) {
        char result[16];
        bstream.read(result);
        cout << "  Result from read(): \"" << result << "\"" << endl;
        int n_correct = 0;
        for (int i = 0; i < bstream.length(); i++) {
            if (expected[i] == result[i]) {
                n_correct++;
            } else {
                break;
            }
        }
        correct = n_correct == 16;
    } else {
        cout << "  Warning: incorrect length of " << bstream.length() << endl;
    }

    // Return the appropriate result
    if (correct) {
        cout << "Success" << endl;
    } else {
        cout << "Failure: got \"" << bstream << "\", expected \"" << expected << "\"" << endl;
    }
    cout << endl;
}

int main() {
    cout << endl << "### TEST for \"BinaryStream.cpp\" ###" << endl << endl;
    test_default();
}