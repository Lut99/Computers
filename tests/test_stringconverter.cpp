/* TEST STRINGCONVERTER.cpp
*    by Lut99
*
*  A test for the StringConverter.
**/

#include <iostream>

#include "../src/support/StringConverter.h"

using namespace std;

int test_uint(unsigned int expected, string to_parse, StringConverter::StringConverterMode mode = StringConverter::NoForgiveness) {
    cout << "Testing UInt (" << StringConverter::StringConverterModeToText[mode] << ")..." << endl;

    cout << "  Test string: \"" << to_parse << "\"" << endl;

    cout << "  Parsing..." << endl;
    unsigned int result;
    try {
        result = StringConverter::toUInt(to_parse, mode);
    } catch (StringConverter::IllegalCharacterException e) {
        cout << "  IllegalCharacterException: " << e.msg << endl;
        cout << "Failure" << endl << endl;
        return -1;
    } catch (StringConverter::NoNumberException e) {
        cout << "  NoNumberException: " << e.msg << endl;
        cout << "Failure" << endl << endl;
        return -2;
    } catch (StringConverter::OverflowException e) {
        cout << "  OverflowException: " << e.msg << endl;
        cout << "Failure" << endl << endl;
        return -3;
    }
    cout << "  Result: " << result << endl;

    if (result == expected) {
        cout << "Success" << endl;
    } else {
        cout << "Failure: expected " << expected << ", got " << result << endl;
    }
    cout << endl;
    return result == expected;
}


int main () {
    cout << endl << "### TEST for \"StringConverter.cpp\" ###" << endl << endl;
    
    // Basic case: check if it parses correctly (strict)
    int randint = rand();
    if (test_uint(randint, to_string(randint)) != 1) {
        cout << "Stop." << endl;
        return 1;
    }
    // Next case: illegalcharacterexception (strict)
    randint = rand();
    if (test_uint(randint, "  " + to_string(randint) + "   ") != -1) {
        cout << "Stop." << endl;
        return 1;
    }
    // Then: OverflowException (strict)
    if (test_uint(0, "16754876125348761235487612534") != -3) {
        cout << "Stop." << endl;
        return 1;
    }
}