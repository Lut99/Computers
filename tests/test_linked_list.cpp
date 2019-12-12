/* TEST_LINKED_LIST.cpp
*    by tHE iNCREDIBLE mACHINE
*
*  A test file for LinkedList.cpp.
**/

#include <iostream>

#include "../src/support/LinkedList.h"

using namespace std;
using namespace DataTypes;

bool test_add() {
    cout << "Testing adding one element and getting it..." << endl;

    LinkedList<int> ls;
    cout << "   Adding 1..." << endl;
    ls.append(1);
    cout << "   Result: " << ls.to_string() << endl;
    cout << "   Get result: " << ls.get(0) << endl;

    if (ls.get(0) == 1) {
        cout << "Success" << endl;
    } else {
        cout << "Error: expected 1, got " << ls.get(0) << endl;
    }
    cout << endl;
}
bool test_add_multiple() {
    cout << "Testing multiple adds and gets..." << endl;

    

    cout << endl;
}
bool test_delete() {
    cout << "Testing delete..." << endl;

    

    cout << endl;
}

int main() {
    cout << endl << "### TEST for \"LinkedList.cpp\" ###" << endl << endl;
    test_add();
    test_add_multiple();
    test_delete();
}