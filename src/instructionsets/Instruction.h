/* INSTRUCTION SET.h
*    by tHE iNCREDIBLE mACHINE
*
*  Header file for InstructionSet.h
**/

#ifndef INSTRUCTIONSET_H
#define INSTRUCTIONSET_H

#include <string>
#include <map>
#include "../include/Version.h"
#include "../Hardware/CPU.h"

namespace Computer {
    struct Instruction {
        /* The code of the instruction */
        const char command;
        /* The size (in bytes) of the assembly instruction */
        const int arg_size;

        /* Instruction struct. Shouldn't be called except from child classes. */
        Instruction(char command, int argument_size);

        /* Virtual void for the fetch step */
        virtual void fetch(char *args);

        /* Virtual void for the execution step */
        virtual void exec(CPU *cpu);
    };

    class InstructionSet {
        public:
            typedef std::map<char, Instruction> InstructionMap;

            /* Returns given instruction class from the instruction set. */
            virtual Instruction get_instr(char command) const;

            /* Returns the name of the instruction set. */
            virtual const std::string get_name() const;
            /* Returns the version of the instruction set. */
            virtual const Version get_version() const;
    };
}

#endif