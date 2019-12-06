/* INSTRUCTION SET.h
*    by tHE iNCREDIBLE mACHINE
*
*  Header file for InstructionSet.h
**/

#ifndef INSTRUCTIONSET_H
#define INSTRUCTIONSET_H

#include <string>
#include <map>
#include "../../CPU.h"

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
        private:
            std::string name;
            char version;

        public:
            typedef std::map<char, Instruction> InstructionMap;

            /* InstructionSet baseclass. Should not be called, except from derived classes. */
            InstructionSet(std::string name, char version);

            /* Used to return the execution function from the derived class */
            virtual Instruction get_instr(char command);

            /* Returns the name of this instructionset */
            const std::string get_name();
            /* Returns the version of this instructionset */
            const char get_version();
            /* Compares the version of this set with a given version number. Return -1 if this one is older, 0 if equal or 1 if newer. */
            const int compare_version(const char version);
    };
}

#endif