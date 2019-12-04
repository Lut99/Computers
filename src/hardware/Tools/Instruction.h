/* INSTRUCTION.h
*    by tHE iNCREDIBLE mACHINE
*
*  Header file for Instruction.cpp
**/

#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <map>

namespace Computer {
    struct Instruction {
        /* The code of the instruction */
        const char command;
        /* The size (in bytes) of the set timssembly instruction */
        const int arg_size;

        /* Instruction struct. Shouldn't be called except from child classes. */
        Instruction(char command);

        /* Virtual void for the fetch step */
        virtual void fetch(char *args);
    };

    /* Instructions */
    struct AddInstruction : public Instruction {
        pointer register_source;
        pointer register_value;
        /* The Add instruction. If called, parses given arguments as if for the Add instruction and stores the values, ready for execution. */
        AddInstruction();
        /* Fetches the instruction, i.e.: parses the data */
        void fetch(char *args);
    };

    /* Creates the appropriate subclass of instruction based on command. */
    Instruction* instructionFactory(char command);
}

#endif