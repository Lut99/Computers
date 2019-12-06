/* COMPUTER.h
*    by tHE iNCREDIBLE mACHINE
*
*  Header file for Computer.cpp.
**/

#ifndef COMPUTER_H
#define COMPUTER_H

#include "CPU.h"
#include "Memory.h"
#include "PCI.h"

namespace Computer {
    class Computer {
        private:
            CPU *cpu;
            Memory *mem;
            // The basic computer has 2 PCI slots
            PCI *components[2];
        public:
            Computer();

            /* Executes one instruction on the Computer */
            void execute();
    };
}

#endif