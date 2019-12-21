/* TEST STRINGCONVERTER.cpp
*    by Lut99
*
*  A test for the StringConverter.
**/

#include <sstream>
#include <iostream>
#include <limits.h>

#include "../src/support/StringConverter.cpp"

using namespace std;

bool test_uint(string msg, int expected_result, unsigned int expected, string to_parse, StringConverter::StringConverterMode mode = StringConverter::NoForgiveness) {
    cout << "Testing UInt : " << msg << "..." << endl;

    cout << "  Test string: \"" << to_parse << "\"" << endl;

    cout << "  Parsing..." << endl;
    unsigned int result;
    try {
        result = StringConverter::toInteger<unsigned int>(to_parse, mode);
    } catch (StringConverter::IllegalCharacterException e) {
        cout << "  IllegalCharacterException: " << e.msg << endl;
        if (expected_result == -1) {
            cout << "Success" << endl << endl;
            return true;
        }
        cout << "Failure" << endl << endl;
        return false;
    } catch (StringConverter::NoNumberException e) {
        cout << "  NoNumberException: " << e.msg << endl;
        if (expected_result == -2) {
            cout << "Success" << endl << endl;
            return true;
        }
        cout << "Failure" << endl << endl;
        return false;
    } catch (StringConverter::OverflowException e) {
        cout << "  OverflowException: " << e.msg << endl;
        if (expected_result == -3) {
            cout << "Success" << endl << endl;
            return true;
        }
        cout << "Failure" << endl << endl;
        return false;
    }
    cout << "  Result: " << result << endl;

    if (result != expected) {
        cout << "  Expected " << expected << ", got " << result << endl;
    }

    if (expected_result == (result == expected)) {
        cout << "Success" << endl << endl;
        return true;
    }
    cout << "Failure" << endl << endl;
    return false;
}
bool test_int(string msg, int expected_result, int expected, string to_parse, StringConverter::StringConverterMode mode = StringConverter::NoForgiveness) {
    cout << "Testing Int : " << msg << "..." << endl;

    cout << "  Test string: \"" << to_parse << "\"" << endl;

    cout << "  Parsing..." << endl;
    int result;
    try {
        result = StringConverter::toInteger<int>(to_parse, mode);
    } catch (StringConverter::IllegalCharacterException e) {
        cout << "  IllegalCharacterException: " << e.msg << endl;
        if (expected_result == -1) {
            cout << "Success" << endl << endl;
            return true;
        }
        cout << "Failure" << endl << endl;
        return false;
    } catch (StringConverter::NoNumberException e) {
        cout << "  NoNumberException: " << e.msg << endl;
        if (expected_result == -2) {
            cout << "Success" << endl << endl;
            return true;
        }
        cout << "Failure" << endl << endl;
        return false;
    } catch (StringConverter::OverflowException e) {
        cout << "  OverflowException: " << e.msg << endl;
        if (expected_result == -3) {
            cout << "Success" << endl << endl;
            return true;
        }
        cout << "Failure" << endl << endl;
        return false;
    } catch (StringConverter::UnderflowException e) {
        cout << "  UnderflowException: " << e.msg << endl;
        if (expected_result == -4) {
            cout << "Success" << endl << endl;
            return true;
        }
        cout << "Failure" << endl << endl;
        return false;
    }
    cout << "  Result: " << result << endl;

    if (result != expected) {
        cout << "  Expected " << expected << ", got " << result << endl;
    }

    if (expected_result == (result == expected)) {
        cout << "Success" << endl << endl;
        return true;
    }
    cout << "Failure" << endl << endl;
    return false;
}


int main () {
    cout << endl << "### TEST for \"StringConverter.cpp\" ###" << endl << endl;
    
    /* Test UINT */
    // Basic case: check if it parses correctly (strict)
    int randint = rand();
    if (!test_uint("Success case", 1, randint, to_string(randint))) {
        return 1;
    }
    // Next case: illegalcharacterexception (strict)
    randint = rand();
    if (!test_uint("IllegalCharacter Case", -1, randint, "a" + to_string(randint))) {
        return 1;
    }
    // Then: OverflowException (strict)
    if (!test_uint("Overflow (easy) case", -3, 0, "16754876125348761235487612534")) {
        return 1;
    }
    // Then: close overflow (strict)
    if (!test_uint("Overflow (just not) case", 1, UINT_MAX, to_string(UINT_MAX))) {
        return 1;
    }
    stringstream sstr;
    string suint_max = to_string(UINT_MAX);
    for (int i = 0; i < suint_max.length() - 1; i++) {
        sstr << suint_max[i];
    }
    sstr << (UINT_MAX - (UINT_MAX / 10 * 10) + 1);
    if (!test_uint("Overflow (just yes) case", -3, 0, sstr.str())) {
        return 1;
    }

    /* Test INT */
    // Basic case: check if it parses correctly (strict)
    randint = 65535;
    if (!test_int("Success case", 1, randint, to_string(randint))) {
        return 1;
    }
    // Also check negative parsing
    randint = -65035;
    if (!test_int("Success case negative", 1, randint, to_string(randint))) {
        return 1;
    }
    // Next case: illegalcharacterexception (strict)
    randint = -1 * rand();
    if (!test_int("IllegalCharacter Case", -1, randint, to_string(randint) + "a")) {
        return 1;
    }
    // Then: OverflowException (strict)
    if (!test_int("Overflow (easy) case", -3, 0, "123412341234123412341234")) {
        return 1;
    }
    if (!test_int("Underflow (easy) case", -4, 0, "-187634816234981762349812763")) {
        return 1;
    }
    // Then: close overflow (strict)
    if (!test_int("Overflow (just not, positive) case", 1, INT_MAX, to_string(INT_MAX))) {
        return 1;
    }
    if (!test_int("Overflow (just not, negative) case", 1, INT_MIN, to_string(INT_MIN))) {
        return 1;
    }

    sstr.str("");
    sstr.clear();
    string sint_max = to_string(INT_MAX);
    for (int i = 0; i < sint_max.length() - 1; i++) {
        sstr << sint_max[i];
    }
    sstr << (INT_MAX - (INT_MAX / 10 * 10) + 1);
    if (!test_int("Overflow (just yes, positive) case", -3, 0, sstr.str())) {
        return 1;
    }

    sstr.str("");
    sstr.clear();
    sstr << "-";
    string sint_min = to_string(INT_MAX);
    for (int i = 0; i < sint_min.length() - 1; i++) {
        sstr << sint_min[i];
    }
    sstr << (INT_MAX - (INT_MAX / 10 * 10) + 2);
    if (!test_int("Overflow (just yes, negative) case", -4, 0, sstr.str())) {
        return 1;
    }

    /* Finally, some tests regarding the different modes. */
    if (!test_int("NoForgiveness w/spaces case", -1, 0, "  657 4887 ")) {
        return 1;
    }
    if (!test_int("AllowSpaces w/spaces case", 1, 6574887, "  657 4887 ", StringConverter::AllowSpaces)) {
        return 1;
    }
    if (!test_int("ParseFirst w/spaces case", 1, 657, "  657 4887 ", StringConverter::ParseFirstNumber)) {
        return 1;
    }
    if (!test_int("ParseLast w/spaces case", 1, 4887, "  657 4887 ", StringConverter::ParseLastNumber)) {
        return 1;
    }
    if (!test_int("NoForgiveness w/chars case", -1, 0, "  657aa 4887 !")) {
        return 1;
    }
    if (!test_int("AllowSpaces w/chars case", -1, 0, "  657aa 4887 !", StringConverter::AllowSpaces)) {
        return 1;
    }
    if (!test_int("ParseFirst w/chars case", 1, 657, "  657aa 4887 !", StringConverter::ParseFirstNumber)) {
        return 1;
    }
    if (!test_int("ParseLast w/chars case", 1, 4887, "  657aa 4887 !", StringConverter::ParseLastNumber)) {
        return 1;
    }
}