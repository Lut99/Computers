/* CPU.h
*    by tHE iNCREDIBLE mACHINE
*
*  Header file for cpu.cpp.
*/

#ifndef CPU_H
#define CPU_H

#include "Memory.h"
#include "Tools/Instruction.h"

namespace Computer {
    class CPU {
        private:
            long *registry;
            float clockspeed;
            pointer program_counter;
            Memory *mem;

            /* Memory access wrapper for the CPU. If the value is a register, returns that register instead. Also errors if out of bounds. */
            void mem_read(char *result, pointer addr, int n);
            /* Memory access wrapper for the CPU. If the value is a register, sets that register instead. Also errors if out of bounds. */
            void mem_write(pointer addr, char *values, int n);
        public:
            /* CPU class. Runs (timssembly) code. The clockspeed is in KHz, the memory is a Memory class and the program_pointer is a pointer in virtual memory that determines which program is run. */
            CPU(float clockspeed, Memory *virt_memory);
            ~CPU();

            /* Executes a single instruction that is next to be executed. The code determines which this is. */
            void execute();

            /* Instruction Execution Units (IEU) */
            
            /* Executes the ADD instruction */
            void execute_add(AddInstruction *to_exec);
    };
}

#endif