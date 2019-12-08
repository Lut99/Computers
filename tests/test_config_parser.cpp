/* TEST_INSTRUCTION.cpp
*    by tHE iNCREDIBLE mACHINE
*
*  A test file for ConfigParser.cpp.
**/

#include <iostream>
#include <fstream>

#include "../src/Hardware/Support/ConfigParser.h"

using namespace std;
using namespace Parser;


bool test_one() {
    cout << "Testing one config..." << endl;

    cout << "   Writing test file ('tests/bin/test1.cfg')..." << endl;
    ofstream test1("tests/bin/test1.cfg");
    test1 << "test=1" << endl;
    test1.close();

    cout << "   Constructing ConfigParser class..." << endl;
    ConfigParser parser("tests/bin/test1.cfg");
    cout << "   Parsing using parse_all()..." << endl;
    parser.parse_all();
    cout << " > Result          : " << parser.to_string() << endl;
    cout << " > Result as string: " << parser.get("test") << endl;
    cout << " > Result as int   : " << parser.get<int>("test") << endl;
    cout << " > Result as float : " << parser.get<float>("test") << endl;
    bool correct = parser.get("test").compare("1") == 0;
    if (correct) {
        cout << "Success" << endl;
    } else {
        cout << "Failure: got \"" + parser.get("test") + "\", expected \"" + "1" + "\"" << endl;
    }
    cout << endl;
}

bool test_mult() {
    cout << "Testing multiple configs..." << endl;

    cout << "   Writing test file ('tests/bin/test2.cfg')..." << endl;
    ofstream test2("tests/bin/test2.cfg");
    test2 << "name=Tim" << endl;
    test2 << "age=20" << endl;
    test2 << "gender=male" << endl;
    test2.close();

    cout << "   Constructing ConfigParser class..." << endl;
    ConfigParser parser("tests/bin/test2.cfg");
    cout << "   Parsing using parse_all()..." << endl;
    parser.parse_all();
    cout << " > Result          : " << parser.to_string() << endl;
    cout << " > Name            : " << parser.get("name") << endl;
    cout << " > Age (as string) : " << parser.get("age") << endl;
    cout << " > Age (as int)    : " << parser.get<int>("age") << endl;
    cout << " > Gender          : " << parser.get("gender") << endl;
    bool correct = parser.get("name").compare("Tim") == 0 && parser.get("age") == "20" && parser.get("gender").compare("male") == 0;
    if (correct) {
        cout << "Success" << endl;
    } else {
        cout << "Failure: expected \"" << "Tim" << "\", \"" << "20" << "\" and \"" << "male" << "\"";
        cout << ", got \"" << parser.get("name") << "\", \"" << parser.get("age") << "\" and \"" << parser.get("gender") << "\"." << endl;
    }
    cout << endl;
}

bool test_comments() {
    cout << "Testing multiple configs with comments..." << endl;

    cout << "   Writing test file ('tests/bin/test3.cfg')..." << endl;
    ofstream test3("tests/bin/test3.cfg");
    test3 << "/* Multiline" << endl;
    test3 << "   comment!*/" << endl;
    test3 << "// Single line comment" << endl;
    test3 << "name=Tim// Single line comment, inline" << endl;
    test3 << "age=/* Multiline comment, inline */20" << endl;
    test3 << "gender=male" << endl;
    test3.close();

    cout << "   Constructing ConfigParser class..." << endl;
    ConfigParser parser("tests/bin/test3.cfg");
    cout << "   Parsing using parse_all()..." << endl;
    parser.parse_all();
    cout << " > Result          : " << parser.to_string() << endl;
    cout << " > Name            : " << parser.get("name") << endl;
    cout << " > Age (as string) : " << parser.get("age") << endl;
    cout << " > Age (as int)    : " << parser.get<int>("age") << endl;
    cout << " > Gender          : " << parser.get("gender") << endl;
    bool correct = parser.get("name").compare("Tim") == 0 && parser.get("age") == "20" && parser.get("gender").compare("male") == 0;
    if (correct) {
        cout << "Success" << endl;
    } else {
        cout << "Failure: expected \"" << "Tim" << "\", \"" << "20" << "\" and \"" << "male" << "\"";
        cout << ", got \"" << parser.get("name") << "\", \"" << parser.get("age") << "\" and \"" << parser.get("gender") << "\"." << endl;
    }
    cout << endl;
}

int main() {
    cout << endl << "### TEST for \"ConfigParser.cpp\" ###" << endl << endl;
    test_one();
    test_mult();
    test_comments();
}