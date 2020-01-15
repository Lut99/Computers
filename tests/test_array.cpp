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
string print_array(Array<int> arr) {
    int result[arr.length()];
    arr.c_arr(result);
    return print_array(result, arr.length());
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

bool test_fixed_static() {
    cout << "Testing array with static initializer..." << endl;

    cout << "  Creating reference array..." << endl;
    int expected[16] = {0, 15, 1, 14, 2, 13, 3, 12, 4, 11, 5, 10, 6, 9, 7, 8};

    cout << "  Creating array..." << endl;
    Array<int> arr = {0, 15, 1, 14, 2, 13, 3, 12, 4, 11, 5, 10, 6, 9, 7, 8};

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

bool test_subset() {
    cout << "Testing array subset..." << endl;

    cout << "  Generating random integer array..." << endl;
    int expected[16];
    for (int i = 0; i < 16; i++) {
        expected[i] = rand();
    }
    cout << "  Generating a subset (range: 0-5)..." << endl;
    int expected_subset_0_5[6];
    for (int i = 0; i < 6; i++) {
        expected_subset_0_5[i] = expected[i];
    }
    cout << "  Generating a subset (range: 6-15)..." << endl;
    int expected_subset_6_15[10];
    for (int i = 6; i < 16; i++) {
        expected_subset_6_15[i - 6] = expected[i];
    }
    cout << "  Generating a subset (range: 3-12)..." << endl;
    int expected_subset_3_12[10];
    for (int i = 3; i < 13; i++) {
        expected_subset_3_12[i - 3] = expected[i];
    }

    cout << "  Creating array (copied)..." << endl;
    Array<int> arr = Array<int>(expected, 16);

    cout << "  Fetching subset from array (range: 0-5): ";
    Array<int> arr_subset_0_5;
    arr.subset(arr_subset_0_5, 0, 6);
    cout << print_array(arr_subset_0_5) << endl;

    cout << "  Fetching subset from array (range: 6-15): ";
    Array<int> arr_subset_6_15;
    arr.subset(arr_subset_6_15, 6);
    cout << print_array(arr_subset_6_15) << endl;

    cout << "  Fetching subset from array (range: 3-12): ";
    Array<int> arr_subset_3_12;
    arr.subset(arr_subset_3_12, 3, 10);
    cout << print_array(arr_subset_3_12) << endl;

    // Check if it is expected
    bool correct_0_5 = true;
    bool correct_6_15 = true;
    bool correct_3_12 = true;
    for (int i = 0; i < 16; i++) {
        if (i < 6 && arr_subset_0_5[i] != expected_subset_0_5[i]) {
            correct_0_5 = false;
            break;
        }
        if (i < 6 && arr_subset_6_15[i] != expected_subset_6_15[i]) {
            correct_6_15 = false;
            break;
        }
        if (i < 10 && arr_subset_3_12[i] != expected_subset_3_12[i]) {
            correct_3_12 = false;
            break;
        }
    }
    if (!correct_0_5) {
        cout << "Failure: expected " << print_array(expected_subset_0_5, 6) << ", got " << print_array(arr_subset_0_5) << endl << endl;
        return false;
    } else if (!correct_6_15) {
        cout << "Failure: expected " << print_array(expected_subset_6_15, 6) << ", got " << print_array(arr_subset_6_15) << endl << endl;
        return false;
    } else if (!correct_3_12) {
        cout << "Failure: expected " << print_array(expected_subset_3_12, 6) << ", got " << print_array(arr_subset_3_12) << endl << endl;
        return false;
    } else {
        cout << "Succes" << endl << endl;
        return true;
    }
}


int main() {
    cout << endl << "### TEST for \"Array.h\" ###" << endl << endl;
    if (!test_fixed_manual()) {
        return 1;
    }
    if (!test_fixed_copy()) {
        return 1;
    }
    if (!test_fixed_static()) {
        return 1;
    }
    if (!test_flexible()) {
        return 1;
    }
    if (!test_subset()) {
        return 1;
    }
}