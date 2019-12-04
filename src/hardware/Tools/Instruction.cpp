/* INSTRUCTION.cpp
*    by tHE iNCREDIBLE mACHINE
*
*  This file contains all instructions that can be found in timssembly, and
*  their unique way to parse them from a string of bytes.
**/

#include <map>

#include "Errors.h"
#include "Instruction.h"
#include "Encoding.h"

using namespace std;
using namespace Computer;

// Init the length map
map<char, int> ArgumentSize = {
    {0x00, 8}
};

Instruction::Instruction(char command)
    : command(command),
    arg_size(ArgumentSize[command])
{}
void Instruction::fetch(char *args) {
    // Do nothing
}

AddInstruction::AddInstruction()
    : Instruction::Instruction(0x00)
{}
void AddInstruction::fetch(char *args) {
    // Parse the arguments as two pointers (signed ints)
    this->register_source = Enc::decode_int(args);
    this->register_value = Enc::decode_int(args + 4);
}

Instruction* Computer::instructionFactory(char command) {
    if (command == 0x00) {
        return new AddInstruction();
    }
    // Unknown instruction
    throw UnknownInstructionException(command, "unknown");
}
