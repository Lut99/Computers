/* TEST_LINKED_LIST.cpp
*    by tHE iNCREDIBLE mACHINE
*
*  A test file for LinkedList.cpp.
**/

#include <iostream>

#include "../src/support/LinkedList.cpp"

using namespace std;
using namespace DataTypes;

bool test_add() {
    cout << "Testing adding one element and getting it..." << endl;

    LinkedList<int> ls;
    ls.append(5);
    cout << "  Appended list : " << ls.to_string() << endl;
    cout << "  .get(0) result: " << ls.get(0) << endl;

    if (ls.get(0) == 5) {
        cout << "Succes" << endl;
    } else {
        cout << "Failure: expected 5, got " << ls.get(0) << endl;
    }

    cout << endl;
}
bool test_add_multiple() {
    cout << "Testing multiple adds and gets..." << endl;

    LinkedList<int> ls;
    ls.append(5);
    ls.append(4);
    ls.append(2);
    ls.append(1);
    ls.insert(2, 3);
    cout << "  Appended list : " << ls.to_string() << endl;
    cout << "  .get(0) result: " << ls.get(0) << endl;
    cout << "  .get(4) result: " << ls.get(4) << endl;

    if (ls.get(0) == 5 && ls.get(4) == 1) {
        cout << "Succes" << endl;
    } else {
        cout << "Failure: expected 5 & 1, got " << ls.get(0) << " and " << ls.get(4) << endl;
    }

    cout << endl;
}
bool test_delete() {
    cout << "Testing delete..." << endl;

    LinkedList<int> ls;
    ls.append(5);
    ls.append(4);
    ls.append(2);
    ls.append(1);
    ls.insert(2, 3);
    ls.remove(3);
    cout << "  Created." << endl;
    cout << "  Appended list : " << ls.to_string() << endl;
    cout << "  .get(0) result: " << ls.get(0) << endl;
    cout << "  .get(3) result: " << ls.get(3) << endl;

    if (ls.get(0) == 5 && ls.get(3) == 1) {
        cout << "Succes" << endl;
    } else {
        cout << "Failure: expected 5 & 1, got " << ls.get(0) << " and " << ls.get(3) << endl;
    }

    cout << endl;
}

int main() {
    cout << endl << "### TEST for \"LinkedList.cpp\" ###" << endl << endl;
    test_add();
    test_add_multiple();
    test_delete();
}