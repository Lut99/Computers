/* Memory.cpp
*    by tHE iNCREDIBLE mACHINE
*
*  The memory for the computers. Should only be used from Computer.cpp.
*  provides random-access memory storage, but then one which isn't declared
*  consecutively in memory. Each line in the address is 64-bit.
*/

#include <iostream>

#include "../support/Errors.h"
#include "Memory.h"

using namespace std;
using namespace Computer;

/* Constructors / Deconstructors */

MemoryCommand::MemoryCommand(HardwareComponent *component, unsigned char operation)
    : Command(component, operation)
{}

Memory::Memory(long size)
    : HardwareComponent(0, "Memory"),
    size(size)
{
    cout << "Initializing Memory (" << this->size << " bytes)..." << endl;

    // Check if size is dividable by MemoryBlockSize
    if (this->size % MemoryBlockSize != 0) {
        throw MemoryBlockMisalignmentException(this->size, MemoryBlockSize);
    }

    // Compute the number of blocks
    this->n_blocks = this->size / MemoryBlockSize;

    // Malloc the memory blocklist
    this->blocks = new char*[this->n_blocks];

    // Set the blocks to NULL
    for (int i = 0; i < this->size; i++) {
        this->blocks[i] = NULL;
    }

    cout << "Memory Initialized." << endl;
}
Memory::~Memory() {
    cout << "Cleaning up Memory..." << endl;

    // Dealloc the blocks (if not NULL)
    for (int i = 0; i < this->n_blocks; i++) {
        if (this->blocks[i] != NULL) {
            delete[] this->blocks[i];
        }
    }

    // Dealloc the list
    delete[] this->blocks;

    cout << "Memory Done." << endl;
}

/* Read / write access for memory */

void Memory::read(pointer addr, char *result, int n) {
    // Check if within bounds and not overflowing
    if (addr < 0 || addr >= this->size) {
        throw MemoryOutOfBoundsException(addr, this->size);
    }
    if (addr + n >= this->size) {
        throw MemoryOverflowException(addr, n, this->size);
    }

    // Split addr into block and index
    int block, index;
    block = addr / MemoryBlockSize;
    index = addr % MemoryBlockSize;

    // Allocate memory if not yet done
    if (this->blocks[block] == NULL) {
        this->blocks[block] = new char[MemoryBlockSize];
    }

    // Copy to the result array
    for (int i = 0; i < n; i++) {
        result[i] = this->blocks[block][index];

        // Increment block and index
        index++;
        if (index >= MemoryBlockSize) {
            index = 0;
            block++;
        }
    }
}
void Memory::write(pointer addr, char *values, int n) {
    // Check if within bounds and not overflowing
    if (addr < 0 || addr >= this->size) {
        throw MemoryOutOfBoundsException(addr, this->size);
    }
    if (addr + n >= this->size) {
        throw MemoryOverflowException(addr, n, this->size);
    }

    // Split addr into block and index
    int block, index;
    block = addr / MemoryBlockSize;
    index = addr % MemoryBlockSize;

    // Allocate memory if not yet done
    if (this->blocks[block] == NULL) {
        this->blocks[block] = new char[MemoryBlockSize];
    }

    // Copy from the values array
    for (int i = 0; i < n; i++) {
        this->blocks[block][index] = values[i];

        // Increment block and index
        index++;
        if (index >= MemoryBlockSize) {
            index = 0;
            block++;
        }
    }
}

/* Hardware Component stuff */

void Memory::_execute_hardware(Command *cmd) {
    // Execute stuff indicated by _to_do:
    MemoryCommand *mem_cmd = (MemoryCommand*) cmd;
    if (cmd->operation == 0x00) {
        // Do a memory read
        this->write(mem_cmd->addr, mem_cmd->result_values, mem_cmd->n);
    } else if (cmd->operation == 0x01) {
        // Do a memory write
        this->read(mem_cmd->addr, mem_cmd->result_values, mem_cmd->n);
    } else {
        // Unknown command
        throw UnknownCommandException(cmd->operation, this->_name);
    }
}
