/* COMPUTER.h
*    by tHE iNCREDIBLE mACHINE
*
*  Header file for Computer.cpp.
**/

#ifndef COMPUTER_H
#define COMPUTER_H

#include <chrono>

#include "CPU.h"
#include "Memory.h"
#include "HardDrive.h"
#include "PCI.h"

namespace Computer {
    class Computer {
        private:
            CPU *cpu;
            Memory *mem;
            HardDrive **drives;
            const int n_drives;
            PCI **components;
            const int n_pci;

            std::chrono::high_resolution_clock::time_point last_clock_cycle;

            Command *waiting_for;
        public:
            /* Creates the computer class. Need to give a type of CPU to use, the memory size (in bytes), the sizes of the harddrives (0 is no drive at that slot) and PCI components used (specify NULL to give no components). */
            Computer(CPUModel cpu_model, long mem_size, int n_drives, long *drive_sizes, int n_components, PCI **pci_components);
            ~Computer();
            
            /* Reads n bytes from main memory at pointer addr and stores the result in the given pointer. */
            void mem_read(pointer addr, char *result, int n);
            /* Writes n bytes from values to main memory at pointer addr. */
            void mem_write(pointer addr, char *values, int n);

            /* HW Execution */
            void execute_hardware();
            /* SW Execution */
            void execute_software();

            friend class CPU;
    };
}

#endif