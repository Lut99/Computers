/* Memory.cpp
*    by tHE iNCREDIBLE mACHINE
*
*  The memory for the computers. Should only be used from Computer.cpp.
*  provides random-access memory storage, but then one which isn't declared
*  consecutively in memory. Each line in the address is 64-bit.
*/

#include <cstddef>

#include "Support/Errors.h"
#include "Memory.h"

using namespace Computer;


/* RAM-memory */
Memory::Memory(long size)
    : size(size) {
    
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


void Memory::read(char *result, pointer addr, int n) {
    // Check for out-of-bounds
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


void Memory::write(pointer addr, char *values, int n) {
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
