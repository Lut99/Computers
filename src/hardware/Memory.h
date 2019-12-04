/* Memory.h
*    by tHE iNCREDIBLE mACHINE
*
*  Header file for Memory.cpp
*/

#ifndef MEMORY_H
#define MEMORY_H

#include "Tools/Instruction.h"
#include "Tools/Types.h"

namespace Computer {
    const int MemoryBlockSize = 32;

    class Memory {
        private:
            EEPROM *eeprom;
            char **blocks;
            long n_blocks;
        public:
            const long size;

            /* Memory class. Is the virtual memory of the computers. Each memory address stands for a char, addressable randomly by the pointer type. */
            Memory(long size, EEPROM *eeprom);
            ~Memory();

            /* Retrieves n bytes of memory from given location. */
            void get(char *result, pointer addr, int n);
            /* Retrieves an instruction from memory. Note: instruction is allocated, so take to deallocate it. */
            void get(Instruction **result, pointer addr);

            /* Sets n bytes at the given location. */
            void set(pointer addr, char *values, int n);
    };

    class EEPROM {
        private:
            const long size = POINTER_EEPROM_SIZE;
            char *memory;
        public:
            /* EEPROM class. Simply a memory of 16 KB, that stores the very first program the computer will run. Is very fast, as it isn't fragmented into blocks, but is also static. */
            EEPROM();
            ~EEPROM();

            /* Gets instruction at given location. Note: instruction is allocated, so don't forget to deallocate it. */
            void get(Instruction **result, pointer addr);
    };
}

#endif