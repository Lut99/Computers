/* TEST BINARYSTREAM.cpp
*    by Lut99
*
*  A test file for the BinaryStream library.
**/

#include <sstream>
#include <iostream>

#include "../include/BinaryStream.h"

using namespace std;
using namespace DataTypes;

std::string print_numerical(char *data, std::size_t size) {
    stringstream sstr;
    for (int i = 0; i < size; i++) {
        if (i > 0) {
            sstr << ", ";
        }
        sstr << ((int) data[i]);
    }
    return sstr.str();
}

bool test_default() {
    cout << "Testing adding of standard types..." << endl;

    cout << "  Creating BinaryStream..." << endl;
    BinaryStream bstream = BinaryStream();
    cout << "  Before adding 36: \"" << bstream.to_string() << "\"" << endl;
    bstream << 36;
    cout << "  Before adding 88: \"" << bstream.to_string() << "\"" << endl;
    bstream << ((unsigned char) 88);
    cout << "  Before adding \"Hello there!\": \"" << bstream.to_string() << "\"" << endl;
    bstream << "Hello there!";
    cout << "  Result: \"" << bstream.to_string() << "\"" << endl;

    // Construct the expected char array
    char expected[128];
    expected[0] = 0;
    expected[1] = 0;
    expected[2] = 0;
    expected[3] = 36;
    expected[4] = 88;
    string hello_there = "Hello there!";
    std::size_t expected_size = 5 + hello_there.length();
    for (int i = 0; i < hello_there.length(); i++) {
        expected[5 + i] = hello_there.c_str()[i];
    }

    // Check the correctness
    bool correct = false;
    if (bstream.length() == expected_size) {
        char result[expected_size];
        bstream.read(result);

        cout << "  Result from read(): \"" << print_numerical(result, bstream.length()) << "\"" << endl;

        int n_correct = 0;
        for (int i = 0; i < bstream.length(); i++) {
            if (expected[i] == result[i]) {
                n_correct++;
            } else {
                break;
            }
        }
        correct = n_correct == expected_size;
    } else {
        cout << "  Warning: incorrect length of " << bstream.length() << " (expected " << expected_size << ")" << endl;
        cout << "  Expected characters (binary): ";
        for (int i = 0; i < expected_size; i++) {
            if (i > 0) {
                cout << ", ";
            }
            cout << ((int) expected[i]);
        }
        cout << endl << "  All characters (binary)     : ";
        char buff[64];
        std::size_t size = bstream.read(buff);
        for (int i = 0; i < size; i++) {
            if (i > 0) {
                cout << ", ";
            }
            cout << ((int) buff[i]);
        }
        cout << endl;
    }

    // Return the appropriate result
    if (correct) {
        cout << "Success" << endl;
    } else {
        cout << "Failure: got \"" << bstream.to_string() << "\", expected \"" << print_numerical(expected, expected_size) << "\"" << endl;
    }
    cout << endl;
}

bool test_binarystring() {
    cout << "Testing addition of BinaryString types..." << endl;

    cout << "  Creating BinaryStream..." << endl;
    BinaryStream bstream = BinaryStream();
    cout << "  Before adding \"Hello there!\": \"" << bstream.to_string() << "\"" << endl;
    bstream << BinaryString("Hello there!");
    cout << "  Before adding '0', '\\', '%', 'a': \"" << bstream.to_string() << "\"" << endl;
    char data[] = {'0', '\\', '%', 'a'};
    bstream << BinaryString(data, 4);
    cout << "  Result: \"" << bstream.to_string() << "\"" << endl;

    // Construct the expected char array
    char expected[128];
    string hello_there = "Hello there!";
    std::size_t expected_size = hello_there.length() + 5;
    for (int i = 0; i < hello_there.length(); i++) {
        expected[i] = hello_there.c_str()[i];
    }
    expected[hello_there.length()] = '\0';
    expected[hello_there.length() + 1] = '0';
    expected[hello_there.length() + 2] = '\\';
    expected[hello_there.length() + 3] = '%';
    expected[hello_there.length() + 4] = 'a';

    // Check the correctness
    bool correct = false;
    if (bstream.length() == expected_size) {
        char result[expected_size];
        bstream.read(result);

        cout << "  Result from read(): \"" << print_numerical(result, bstream.length()) << "\"" << endl;

        int n_correct = 0;
        for (int i = 0; i < bstream.length(); i++) {
            if (expected[i] == result[i]) {
                n_correct++;
            } else {
                break;
            }
        }
        correct = n_correct == expected_size;
    } else {
        cout << "  Warning: incorrect length of " << bstream.length() << " (expected " << expected_size << ")" << endl;
        cout << "  Expected characters (binary): ";
        for (int i = 0; i < expected_size; i++) {
            if (i > 0) {
                cout << ", ";
            }
            cout << ((int) expected[i]);
        }
        cout << endl << "  All characters (binary)     : ";
        char buff[64];
        std::size_t size = bstream.read(buff);
        for (int i = 0; i < size; i++) {
            if (i > 0) {
                cout << ", ";
            }
            cout << ((int) buff[i]);
        }
        cout << endl;
    }

    // Return the appropriate result
    if (correct) {
        cout << "Success" << endl;
    } else {
        cout << "Failure: got \"" << bstream.to_string() << "\", expected \"" << print_numerical(expected, expected_size) << "\"" << endl;
    }
    cout << endl;
}

int main() {
    cout << endl << "### TEST for \"BinaryStream.cpp\" ###" << endl << endl;
    test_default();
    test_binarystring();
}