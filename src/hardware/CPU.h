/* CPU.h
*    by tHE iNCREDIBLE mACHINE
*
*  Header file for cpu.cpp.
*/

#ifndef CPU_H
#define CPU_H

#include "Memory.h"
#include "Support/InstructionSets/Instruction.h"

namespace Computer {
    class CPU {
        private:
            long *registry_file;
            float clockspeed;
            Memory *mem;
            InstructionSet *instr_set;

            /* Keeps track of where the CPU is with execution in memory */
            pointer program_counter;

            /* Memory access wrapper for code. What instructions are supported is entirely dependent on the instruction set used. */
            Instruction mem_fetch(pointer addr);
        public:
            /* CPU class. Runs assembly from an Instruction Set. The 'virt_memory' argument should be the memory attached to this computer. */
            CPU(Memory *virt_memory);
            ~CPU();

            /* Register read access for the CPU. No masking is applied, so the full register is returned. */
            long reg_read(int reg);
            /* Register read access for the CPU. Only returns the last 4 bytes so that an int is returned. */
            int reg_read_4(int reg);
            /* Register read access for the CPU. Only returns the last 2 bytes so that a short is returned. */
            short reg_read_2(int reg);
            /* Register read access for the CPU. Only returns the last byte so that a char is returned. */
            char reg_read_1(int reg);

            /* Register write access for the CPU. No masking is applied to the input, so the register is completely overwritted. */
            void reg_write(int reg, long value);
            /* Register write access for the CPU. Only the last 4 bytes are overwritten, so that an int can be set. */
            void reg_write(int reg, int value);
            /* Register write access for the CPU. Only the last 2 bytes are overwritten, so that a short can be set. */
            void reg_write(int reg, short value);
            /* Register write access for the CPU. Only the last byte is overwritten, so that a char can be set. */
            void reg_write(int reg, char value);

            /* Memory access wrapper for the CPU. */
            void mem_read(char *result, pointer addr, int n);
            /* Memory access wrapper for the CPU. */
            void mem_write(pointer addr, char *values, int n);

            /* Executes a single instruction that is next to be executed. The code determines which this is. */
            void execute();
    };
}

#endif