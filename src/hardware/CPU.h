/* CPU.h
*    by tHE iNCREDIBLE mACHINE
*
*  Header file for cpu.cpp.
*/

#ifndef CPU_H
#define CPU_H

#include <string>
#include "Computer.h"
#include "Memory.h"
#include "Support/InstructionSets/Instruction.h"

namespace Computer {
    enum CPUModel {
        Medusa_I
    };

    struct CPUConfig {
        const CPUModel model;
        const std::string name;
        const int clockspeed;
        const long clocktime;
        const InstructionSet *instr_set;
        
        /* Stores information regarding the CPU models */
        CPUConfig(CPUModel model, std::string name, int clockspeed, InstructionSet *instr_set);
    };

    /* Maps a CPUModel to the CPU config required */
    const CPUConfig CPUModel_config[] = {
        CPUConfig(Medusa_I, "Medusa_I", 100, NULL)
    };

    class CPU {
        private:
            long *registry_file;

            /* Reference to the Computer for hardware access */
            Computer *comp;

            /* Keeps track of where the CPU is with execution in memory */
            pointer program_counter;

            /* Memory access wrapper for code. What instructions are supported is entirely dependent on the instruction set used. */
            Instruction mem_fetch(pointer addr);
        public:
            /* Keeps track of the specific CPU information */
            const CPUConfig info;

            /* CPU class. Runs assembly from an Instruction Set. The 'virt_memory' argument should be the memory attached to this computer. */
            CPU(CPUModel model, Computer *computer);
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
            void mem_read(pointer addr, char *result, int n);
            /* Memory access wrapper for the CPU. */
            void mem_write(pointer addr, char *values, int n);

            /* Executes a single instruction that is next to be executed. The code determines which this is. */
            void execute();
    };
}

#endif