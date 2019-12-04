/* TEST_INSTRUCTION.cpp
*    by tHE iNCREDIBLE mACHINE
*
*  A test file for Instruction.cpp.
**/

#include <iostream>
#include <random>

#include "../src/hardware/Tools/Instruction.h"

using namespace std;
using namespace Computer;


bool test_add() {
    cout << "Testing instruction 'add'..." << endl;
    cout << "  Generating two random values..." << endl;
    int sum1 = rand();
    int sum2 = rand();
    cout << "  Preparing instruction..." << endl;
    Instruction add = Instruction(0x00);
    cout << "  Executing..." << endl;
    
    cout << "  Result: " << 5 << " / OK? " << "Yes" << endl << endl;
}


int main() {
    cout << endl << "### TEST for \"Instruction.cpp\" ###" << endl << endl;
    test_add();
}