/* TEST_ARRAY.cpp
*    by tHE iNCREDIBLE mACHINE
*
*  A test file for Array.h.
**/

#include <random>
#include <iostream>
#include <sstream>

#include "../src/include/Array.h"

using namespace std;
using namespace DataTypes;

string print_array(int *arr, std::size_t size) {
    stringstream sstr;
    sstr << "[";
    for (int i = 0; i < size; i++) {
        if (i > 0) {
            sstr << ", ";
        }
        sstr << arr[i];
    }
    sstr << "]";
    return sstr.str();
}


bool test_fixed_manual() {
    cout << "Testing array with fixed size, manual copying..." << endl;

    cout << "  Generating random integer array..." << endl;
    int expected[16];
    for (int i = 0; i < 16; i++) {
        expected[i] = rand();
    }

    cout << "  Creating array..." << endl;
    Array<int> arr = Array<int>(16);

    cout << "  Populating array..." << endl;
    for (int i = 0; i < 16; i++) {
        arr[i] = expected[i];
    }

    int result[16];
    arr.c_arr(result);
    cout << "  Result: " << print_array(result, 16) << endl;

    // Check if it is expected
    bool correct = true;
    for (int i = 0; i < 16; i++) {
        if (result[i] != expected[i]) {
            correct = false;
            break;
        }
    }
    if (correct) {
        cout << "Succes" << endl << endl;
    } else {
        cout << "Failure: expected " << print_array(expected, 16) << ", got " << print_array(result, 16) << endl << endl;
    }
    return correct;
}

bool test_fixed_copy() {
    cout << "Testing array with fixed size, automatic copying..." << endl;

    cout << "  Generating random integer array..." << endl;
    int expected[16];
    for (int i = 0; i < 16; i++) {
        expected[i] = rand();
    }

    cout << "  Creating array..." << endl;
    Array<int> arr = Array<int>(expected, 16);

    int result[16];
    arr.c_arr(result);
    cout << "  Result: " << print_array(result, 16) << endl;

    // Check if it is expected
    bool correct = true;
    for (int i = 0; i < 16; i++) {
        if (result[i] != expected[i]) {
            correct = false;
            break;
        }
    }
    if (correct) {
        cout << "Succes" << endl << endl;
    } else {
        cout << "Failure: expected " << print_array(expected, 16) << ", got " << print_array(result, 16) << endl << endl;
    }
    return correct;
}

bool test_flexible() {
    cout << "Testing array with flexible size..." << endl;

    cout << "  Generating random integer array..." << endl;
    int expected[16];
    for (int i = 0; i < 16; i++) {
        expected[i] = rand();
    }

    cout << "  Creating array..." << endl;
    Array<int> arr;

    cout << "  Populating array..." << endl;
    for (int i = 0; i < 16; i++) {
        arr.append(expected[i]);
    }

    int result[16];
    arr.c_arr(result);
    cout << "  Result: " << print_array(result, 16) << endl;

    // Check if it is expected
    bool correct = true;
    for (int i = 0; i < 16; i++) {
        if (result[i] != expected[i]) {
            correct = false;
            break;
        }
    }
    if (correct) {
        cout << "Succes" << endl << endl;
    } else {
        cout << "Failure: expected " << print_array(expected, 16) << ", got " << print_array(result, 16) << endl << endl;
    }
    return correct;
}


int main() {
    cout << endl << "### TEST for \"Array.h\" ###" << endl << endl;
    if (!test_fixed_manual()) {
        return 1;
    }
    if (!test_fixed_copy()) {
        return 1;
    }
    if (!test_flexible()) {
        return 1;
    }
}