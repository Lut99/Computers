/* CHAOS v1.0 INSTRUCTION SET
*    by Lut99
*
*  Header file for chaos_1_0.cpp.
**/

#ifndef CHAOS_1_0_H
#define CHAOS_1_0_H

#include "Instruction.h"

namespace Computer {
    namespace Chaos1_0 {
        class Set : public InstructionSet {
            private:
                /* Maps given command to given instruction, length-wise */
                static std::map<char, int> instrSize;
                /* Maps given command to given execution function */
                static std::map<char, void (Instruction::*)(CPU *cpu)> instrExec;

            public:
                /* Returns given instruction class from the instruction set. */
                Instruction get_instr(char command) const;

                /* Returns the name of the instruction set. */
                const std::string get_name() const;
                /* Returns the version of the instruction set. */
                const Version get_version() const;
        };

        /* INSTRUCTIONS */
        class AddInstruction : public Instruction {
            // TODO
        };
    }
}

#endif