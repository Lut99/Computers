/* Memory.cpp
*    by tHE iNCREDIBLE mACHINE
*
*  The memory for the computers. Should only be used from Computer.cpp.
*  provides random-access memory storage, but then one which isn't declared
*  consecutively in memory. Each line in the address is 64-bit.
*/

#include <cstddef>

#include "Tools/Errors.h"
#include "Memory.h"

using namespace Computer;


/* RAM-memory */
Memory::Memory(long size, EEPROM *eeprom)
    : size(size) {
    // Store the eeprom pointer
    this->eeprom = eeprom;
    
    // Check if size is dividable by MemoryBlockSize
    if (this->size % MemoryBlockSize != 0) {
        throw MemoryBlockMisalignmentException(this->size, MemoryBlockSize);
    }

    // Compute the number of blocks
    this->n_blocks = this->size / MemoryBlockSize;

    // Malloc the memory blocklist
    this->blocks = new char*[this->n_blocks];

    // Malloc the blocks
    for (int i = 0; i < this->size; i++) {
        this->blocks[i] = new char[MemoryBlockSize];
    }
}
Memory::~Memory() {
    // Dealloc the blocks
    for (int i = 0; i < this->n_blocks; i++) {
        delete[] this->blocks[i];
    }

    // Dealloc the list
    delete[] this->blocks;
}

void Memory::get(char *result, pointer addr, int n) {
    // Check for out-of-bounds. Ignore special cases, as registries are handled
    //   by CPU and EEPROM is only for instructions.
    if (addr < 0 || addr >= this->size) {
        throw MemoryOutOfBoundsException(addr, this->size);
    }
    
    // Check for overflows
    if (addr + n >= this->size) {
        throw MemoryOverflowException(addr, n, this->size);
    }

    // Now that's done, split pointer into memory block and memory index
    int block, index;
    block = addr / this->n_blocks;
    index = addr % this->n_blocks;

    // Now fetch the given n bytes and return it in result
    for (int i = 0; i < n; i++) {
        result[i] = this->blocks[block][index];
        index++;
        if (index >= MemoryBlockSize) {
            block++;
            index = 0;
        }
    }
}
void Memory::get(Instruction **result, pointer addr) {
    // First, check if there is EEPROM memory called upon
    if (addr < 16) {
        // It is, so call upon the EEPROM instead
        pointer addr_eeprom = addr + POINTER_EEPROM;
        return this->eeprom->get(result, addr_eeprom);
    }

    // Check if the pointer is within bounds
    if (addr < 0 || addr >= this->size) {
        throw MemoryOutOfBoundsException(addr, this->size);
    }

    // Split pointer into memory block and memory index
    int block, index;
    block = addr / this->n_blocks;
    index = addr % this->n_blocks;
    
    // Find the instruction type and cast it to the approriate type
    Instruction *to_return = instructionFactory(this->blocks[block][index]);

    // Check for overflows
    if (addr + to_return->arg_size >= this->size) {
        throw MemoryOverflowException(addr, to_return->arg_size, this->size);
    }

    // There are none. Now, collect the argument in a char array
    char args[to_return->arg_size];
    for (int i = 0; i < to_return->arg_size; i++) {
        args[i] = this->blocks[block][index];
        index++;
        if (index >= MemoryBlockSize) {
            block++;
            index = 0;
        }
    }
    
    // Fetch and return
    to_return->fetch(args);
    (*result) = to_return;
}

void Memory::set(pointer addr, char *values, int n) {
    // First, check for out-of-bounds and everything
    if (addr < 0 || addr >= this->size) {
        throw MemoryOutOfBoundsException(addr, this->size);
    }
    
    // Check for overflows
    if (addr + n >= this->size) {
        throw MemoryOverflowException(addr, n, this->size);
    }

    // Then, compute block and index
    int block, index;
    block = addr / this->n_blocks;
    index = addr % this->n_blocks;

    // Set the new data
    for (int i = 0; i < n; i++) {
        this->blocks[block][index] = values[i];
        index++;
        if (index >= MemoryBlockSize) {
            block++;
            index = 0;
        }
    }
}


/* EEPROM (bios flash memory) */
EEPROM::EEPROM() {
    // Initialize the memory
    this->memory = new char[this->size];
}
EEPROM::~EEPROM() {
    // Delete the memory
    delete[] this->memory;
}
void EEPROM::get(Instruction **result, pointer addr) {
    // Check if address is within bounds
    if (addr < 0 || addr >= this->size) {
        throw MemoryOutOfBoundsException(addr, this->size);
    }

    // Create the appropriate instruction object
    Instruction *to_return = instructionFactory(this->memory[addr]);

    // Check if we're overflowing or not
    if (addr + to_return->arg_size >= this->size) {
        throw MemoryOverflowException(addr, to_return->arg_size, this->size);
    }

    // All clear; parse and return
    to_return->fetch(this->memory + addr);
    // Return
    (*result) = to_return;
}
