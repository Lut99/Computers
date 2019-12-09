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
                virtual Instruction get_instr(char command) const;

                /* Returns the name of the instruction set. */
                virtual const std::string get_name() const;
                /* Returns the version of the instruction set. */
                virtual const Version get_version() const;
        };

        /* INSTRUCTIONS */
        class AddInstruction : public Instruction {
            private:
                char reg_1;
                char reg_2;
            public:
                const static char command = 0x00;

                /* The AddInstruction adds two register values to each other, and outputs the result in the first one. */
                AddInstruction();

                /* Parses arguments for the Add instruction (2x a char for registers) */
                void fetch(char *args);

                /* Executes the instruction (adds the two register values together, outputs the result in the first) */
                void exec(CPU *cpu);
        };

        class SetInstruction : public Instruction {
            private:
                char reg;
                long value;
            public:
                const static char command = 0x01;

                /* The SetInstruction sets a register to a particular value */
                SetInstruction();

                /* Parses arguments for the Set instruction (1x char for register, 1x long for value) */
                void fetch(char *args);

                /* Executes the instruction (sets the given register to the given value) */
                void exec(CPU *cpu);
        };

        class OutputInstruction : public Instruction {
            private:
                char reg;
            public:
                const static char command = 0x02;

                /* The SetInstruction prints the value of a register to the output */
                OutputInstruction();

                /* Parses arguments for the Set instruction (1x char for register) */
                void fetch(char *args);

                /* Executes the instruction (shows the given register on the output) */
                void exec(CPU *cpu);
        };
    }
}

#endif