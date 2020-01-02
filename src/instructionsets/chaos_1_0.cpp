/* CHAOS v1.0 INSTRUCTION SET
*    by Lut99
*
*  The simplest and earliest instruction set out there. Able to perform a
*  simple list of additions, substractions, and memory reads and writes.
**/

#include <iostream>

#include "../include/Encoding.h"
#include "../include/Errors.h"
#include "chaos_1_0.h"

using namespace Computer;
using namespace Chaos1_0;

Instruction Set::get_instr(char command) const {
    if (command == AddInstruction::command) {
        return AddInstruction();
    }
    // Unknown instruction
    throw UnknownInstructionException(command, Set::get_name());
}
const std::string Set::get_name() const {
    return "Chaos";
}
const Version Set::get_version() const {
    return Version(1, 0, 0);
}

/* INSTRUCTIONS */
AddInstruction::AddInstruction()
    : Instruction(this->command, 2)
{}
void AddInstruction::fetch(char *args) {
    // Simply copy the first two bytes
    this->reg_1 = args[0];
    this->reg_2 = args[1];
}
void AddInstruction::exec(CPU *cpu) {
    // Fetch the register data
    long reg_1_data = cpu->reg_read(this->reg_1);
    long reg_2_data = cpu->reg_read(this->reg_2);
    // Do the multiplication and write back
    cpu->reg_write(this->reg_1, reg_1_data + reg_2_data);
}

SetInstruction::SetInstruction()
    : Instruction(this->command, 9)
{}
void SetInstruction::fetch(char *args) {
    // Simply copy the first byte for register value
    this->reg = args[0];
    // And the other 8 bytes as long
    this->value = Enc::decode_long(args + 1);
}
void SetInstruction::exec(CPU *cpu) {
    // Simply set the value
    cpu->reg_write(this->reg, this->value);
}

OutputInstruction::OutputInstruction()
    : Instruction(this->command, 1)
{}
void OutputInstruction::fetch(char *args) {
    // Simply copy the first byte for register value
    this->reg = args[0];
}
void OutputInstruction::exec(CPU *cpu) {
    // Simply set the value
    std::cout << "Register " << this->reg << ": \"" << cpu->reg_read(this->reg) << "\"" << std::endl;
}