/* Memory.h
*    by tHE iNCREDIBLE mACHINE
*
*  Header file for Memory.cpp
*/

#ifndef MEMORY_H
#define MEMORY_H

#include "HardwareComponent.h"
#include "Types.h"

namespace Computer {
    const int MemoryBlockSize = 1024;

    struct MemoryCommand : public Command {
        char *result_values;
        pointer addr;
        int n;

        MemoryCommand(HardwareComponent *component, unsigned char operation);
    };

    class Memory : public HardwareComponent {
        private:
            char **blocks;
            long n_blocks;

        protected:
            /* Overrides the HardwareComponent _execute_hardware(). This function executes the hardware side of Memory. */
            void _execute_hardware(Command *cmd);

        public:
            const long size;

            /* Memory class. Is the virtual memory of the computers. Each memory address stands for a char, addressable randomly by the pointer type. */
            Memory(long size);
            ~Memory();

            /* Retrieves n bytes of memory from given location. */
            void read(pointer addr, char *result, int n);

            /* Sets n bytes at the given location. */
            void write(pointer addr, char *values, int n);
    };
}

#endif