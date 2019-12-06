/* Memory.h
*    by tHE iNCREDIBLE mACHINE
*
*  Header file for Memory.cpp
*/

#ifndef MEMORY_H
#define MEMORY_H

#include "Support/InstructionSets/Instruction.h"
#include "Support/Types.h"

namespace Computer {
    const int MemoryBlockSize = 32;

    class Memory {
        private:
            char **blocks;
            long n_blocks;
        public:
            const long size;

            /* Memory class. Is the virtual memory of the computers. Each memory address stands for a char, addressable randomly by the pointer type. */
            Memory(long size);
            ~Memory();

            /* Retrieves n bytes of memory from given location. */
            void read(char *result, pointer addr, int n);

            /* Sets n bytes at the given location. */
            void write(pointer addr, char *values, int n);
    };
}

#endif