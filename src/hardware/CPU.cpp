/* CPU.cpp
*    by tHE iNCREDIBLE mACHINE
*
*  The tim-assembly executor for the computers. Should be called from Computer.cpp
*  only, which allows all hardware to work together. The cpu exists out of a
*  registry file and is able to execute one timssembly line per clock cycle.
*  In general, one can expect every instruction to have the same execution
*  time.
*/

#include "Support/Encoding.h"
#include "Support/Errors.h"
#include "CPU.h"

#define N_REGISTERS 16

using namespace Computer;

CPU::CPU(Memory *virt_memory) {
    // Set the given data
    this->mem = virt_memory;

    // Initialize the PC to the first EEPROM address
    this->program_counter = POINTER_EEPROM;

    // Initialize the registry file as N_REGISTERS longs
    this->registry_file = new long[N_REGISTERS];

    // Initialize everything for derived classes to NULL or -1
    this->clockspeed = -1;
    this->instr_set = NULL;
}
CPU::~CPU() {
    // Deallocate the registry
    delete[] this->registry_file;
    // Also, possibly, deallocate the instruction set
    if (this->instr_set != NULL) {
        delete this->instr_set;
    }
}

/* CPU-only instruction fetch. */

Instruction CPU::mem_fetch(pointer addr) {
    // First, fetch the command from the pointer
    char command;
    this->mem->read(&command, addr, 1);
    
    // Try to create an instruction from our instructionset
    Instruction to_return = this->instr_set->get_instr(command);

    // Read the arguments
    char args[to_return.arg_size];
    this->mem->read(args, addr + 1, to_return.arg_size);

    // Parse them in the instruction
    to_return.fetch(args);

    // Done, return
    return to_return;
}

/* Registry read access wrappers */

long CPU::reg_read(int reg) {
    // Check if reg is within bounds
    if (reg < 0 || reg >= N_REGISTERS) {
        throw RegistryOutOfBoundsException(reg, N_REGISTERS);
    }
    // It's not; return the value of it
    return this->registry_file[reg];
}
int CPU::reg_read_4(int reg) {
    // Get the long value
    long res = this->reg_read(reg);
    // Mask and cast to int, return
    return (int) (res & 0xFFFFFFFF);
}
short CPU::reg_read_2(int reg) {
    // Get the long value
    long res = this->reg_read(reg);
    // Mask and cast to short, return
    return (short) (res & 0xFFFF);
}
char CPU::reg_read_1(int reg) {
    // Get the long value
    long res = this->reg_read(reg);
    // Mask and cast to short, return
    return (char) (res & 0xFF);
}

/* Registry write access wrappers */

void CPU::reg_write(int reg, long value) {
    // Check if registry access is valid
    if (reg < 0 || reg >= N_REGISTERS) {
        throw RegistryOutOfBoundsException(reg, N_REGISTERS);
    }
    // It is; set the value
    this->registry_file[reg] = value;
}
void CPU::reg_write(int reg, int value) {
    this->reg_write(reg, (long) value);
}
void CPU::reg_write(int reg, short value) {
    this->reg_write(reg, (long) value);
}
void CPU::reg_write(int reg, char value) {
    this->reg_write(reg, (long) value);
}

/* Memory access wrappers */

void CPU::mem_read(char *result, pointer addr, int n) {
    this->mem->read(result, addr, n);
}
void CPU::mem_write(pointer addr, char *values, int n = 4) {
    this->mem->write(addr, values, n);
}

void CPU::execute() {
    // Read the instruction from memory
    Instruction to_exec = this->mem_fetch(this->program_counter);

    // Execute it
    to_exec.exec(this);

    // Increment program counter with the instruction size
    this->program_counter += to_exec.arg_size + 1;
}
