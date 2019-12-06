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

Instruction::Instruction(char command, int argument_size)
    : command(command),
    arg_size(argument_size)
{}
void Instruction::fetch(char *args) {
    /* Not implemented; throw error */
    throw NoOverrideException("Instruction::fetch");
}

InstructionSet::InstructionSet(string name, char version) {
    this->name = name;
    this->version = version;
}
Instruction InstructionSet::get_instr(char command) {
    /* Not implemented; throw error */
    throw NoOverrideException("InstructionSet::get_instr");
}
const string InstructionSet::get_name() {
    return this->name;
}
const char InstructionSet::get_version() {
    return this->version;
}
const int InstructionSet::compare_version(const char version) {
    if (this->version < version) {
        return -1;
    } else if (this->version == version) {
        return 0;
    } else {
        return 1;
    }
}