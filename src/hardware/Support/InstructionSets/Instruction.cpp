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


Instruction InstructionSet::get_instr(char command) const {
    /* Not implemented; throw error */
    throw NoOverrideException("InstructionSet::get_instr");
}
const std::string InstructionSet::get_name() const {
    /* Not implemented; throw error */
    throw NoOverrideException("InstructionSet::get_name");
}
const Version InstructionSet::get_version() const {
    /* Not implemented; throw error */
    throw NoOverrideException("InstructionSet::get_version");
}