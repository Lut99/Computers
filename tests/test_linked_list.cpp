/* TEST_LINKED_LIST.cpp
*    by tHE iNCREDIBLE mACHINE
*
*  A test file for LinkedList.cpp.
**/

#include <iostream>
#include <sstream>

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
bool test_array() {
    cout << "Testing to_array..." << endl;

    LinkedList<int> ls;
    ls.append(5);
    ls.append(4);
    ls.append(2);
    ls.append(1);
    ls.insert(2, 3);
    ls.remove(3);

    cout << "  Appended list : " << ls.to_string() << endl;
    stringstream sstr;
    int *a = ls.to_array();
    bool is_correct = true;
    sstr << "[";
    for (int i = 0; i < ls.length(); i++) {
        if (i > 0) {
            sstr << ", ";
        }
        sstr << a[i];
        // Also check correctness
        is_correct = is_correct && a[i] == ls.get(i);
    }

    sstr << "]" << endl;
    string result = sstr.str();

    cout << "  Appended array: " << result << endl;
    
    if (is_correct) {
        cout << "Succes" << endl;
    } else {
        cout << "Failure: expected " << ls.to_string() << ", got " << result << endl;
    }
    delete[] a;

    cout << endl;
}
bool test_iterator() {
    cout << "Testing LinkedListIterator..." << endl;

    LinkedList<int> ls;
    ls.append(5);
    ls.append(4);
    ls.append(2);
    ls.append(1);
    ls.insert(2, 3);
    ls.remove(3);

    cout << "  Appended list  : " << ls.to_string() << endl;
    cout << "  Iterated result: ";
    int value;
    int i = 0;
    bool is_correct = true;
    stringstream incorrect_list;
    incorrect_list << "[";
    for (LinkedListIterator iter(ls); iter.next(value);) {
        if (i > 0) {
            cout << ", ";
            incorrect_list << ", ";
        }
        cout << value;

        // Also check the result
        is_correct = is_correct && value == ls.get(i);
        incorrect_list << value;

        i++;
    }
    cout << endl;
    incorrect_list << "]";
    
    if (is_correct) {
        cout << "Succes" << endl;
    } else {
        cout << "Failure: expected " << ls.to_string() << ", got " << incorrect_list.str() << endl;
    }

    cout << endl;
}

int main() {
    cout << endl << "### TEST for \"LinkedList.cpp\" ###" << endl << endl;
    test_add();
    test_add_multiple();
    test_delete();
    test_array();
    test_iterator();
}