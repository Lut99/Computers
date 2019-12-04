/* CPU.cpp
*    by tHE iNCREDIBLE mACHINE
*
*  The tim-assembly executor for the computers. Should be called from Computer.cpp
*  only, which allows all hardware to work together. The cpu exists out of a
*  registry file and is able to execute one timssembly line per clock cycle.
*  In general, one can expect every instruction to have the same execution
*  time.
*/

#include "Tools/Encoding.h"
#include "Errors.h"
#include "CPU.h"

#define N_REGISTERS 16

using namespace Computer;

CPU::CPU(float clockspeed, Memory *virt_memory) {
    // Set the given data
    this->clockspeed = clockspeed;
    this->mem = virt_memory;
    // Initialize the PC to the first EEPROM address
    this->program_counter = POINTER_EEPROM;

    // Initialize the registry file as N_REGISTERS longs
    this->registry = new long[N_REGISTERS];
}
CPU::~CPU() {
    // Deallocate the registry
    delete[] this->registry;
}

/* Memory access wrappers */
void CPU::mem_read(char *result, pointer addr, int n = 4) {
    // Checks if within bounds
    if (addr >= -16 && addr <= -1) {
        char reg = abs(addr) - 1;
        // Get the registry value
        Enc::encode(result, this->registry[reg]);
        // Mask according to n
        if (n == 1) {
            result[0] = 0;
            result[1] = 0;
            result[2] = 0;
        } else if (n == 2) {
            result[0] = 0;
            result[1] = 0;
        } else if (n != 4) {
            throw RegistryException(n);
        }
        return;
    }
    // Else, delegate to memory
    return this->mem->get(result, addr, n);
}
void CPU::mem_write(pointer addr, char *values, int n = 4) {
    // Checks if within bounds
    if (addr >= -16 && addr <= -1) {
        // Set the registry value
        char reg = abs(addr) - 1;
        // Determine how to decode by n
        if (n == 1) {
            this->registry[reg] = Enc::decode_char(values);
        } else if (n == 2) {
            this->registry[reg] = Enc::decode_short(values);
        } else if (n == 4) {
            this->registry[reg] = Enc::decode_long(values);
        } else {
            throw RegistryException(n);
        }
        return;
    }
    // Else, do memory
    return this->mem->set(addr, values, n);
}

void CPU::execute() {
    // Read the instruction from memory
    Instruction *to_exec;
    this->mem->get(&to_exec, this->program_counter);

    // Execute it
    if (to_exec->command == 0x00) {
        this->execute_add((AddInstruction*) to_exec);
    }

    // Dealloc the instruction
    delete to_exec;
}

void CPU::execute_add(AddInstruction *to_exec) {
    // Get the values from given registers / memory addresses
    char data[4];
    this->mem_read(data, to_exec->register_source);
    long value1 = Enc::decode_long(data);
    this->mem_read(data, to_exec->register_value);
    long value2 = Enc::decode_long(data);

    // Execute the operation
    value1 += value2;

    // Write to memory again
    Enc::encode(data, value1);
    this->mem_write(to_exec->register_source, data);
}