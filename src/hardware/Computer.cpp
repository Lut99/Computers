/* COMPUTER.cpp
*    by tHE iNCREDIBLE mACHINE
*
*  This file is the overarching file for the Computer. It is where components
*  are installed and communication between them happens. Currently, there is
*  only one computer, but there might be more different configurations in the
*  future.
**/

#include "Support/Errors.h"
#include "Computer.h"

using namespace Computer;

Computer::Computer::Computer(CPU *cpu, long mem_size, int n_drives, long *drive_sizes, int n_components, PCI **pci_components)
    :n_drives(n_drives),
    n_pci(n_components)
{
    // Store the CPU
    this->cpu = cpu;

    // Create the memory with given size
    this->mem = new Memory(mem_size);

    // Create harddrives according to the given sizes
    this->drives = new HardDrive*[this->n_drives];
    for (int i = 0; i < n_drives; i++) {
        this->drives[i] = new HardDrive();
    }

    // Set the given PCI Components
    this->components = new PCI*[this->n_pci];
    for (int i = 0; i < n_components; i++) {
        this->components[i] = pci_components[i];
    }

    this->waiting_for = NULL;

    this->last_clock_cycle = std::chrono::system_clock::now();
}
Computer::Computer::~Computer() {
    // Destroy everything
    delete this->cpu;
    delete this->mem;

    for (int i = 0; i < this->n_drives; i++) {
        delete this->drives[i];
    }
    delete[] this->drives;

    for (int i = 0; i < this->n_pci; i++) {
        delete this->components[i];
    }
    delete[] this->components;
}

void Computer::Computer::mem_read(pointer addr, char *result, int n) {
    // Check if the computer isn't already waiting
    if (this->waiting_for != NULL) {
        throw CommandQueueOverflowException(1, 1, "ComputerQueue");
    }

    // Set the command to be run
    MemoryCommand *mem_cmd = new MemoryCommand(this->mem, 0x00);
    mem_cmd->addr = addr;
    mem_cmd->result_values = result;
    mem_cmd->n = n;

    // Set this computer's status to waiting
    this->waiting_for = (Command*) mem_cmd;
}
void Computer::Computer::mem_write(pointer addr, char *values, int n) {
    // Check if the computer isn't already waiting
    if (this->waiting_for != NULL) {
        throw CommandQueueOverflowException(1, 1, "ComputerQueue");
    }

    // Set the command to be run
    MemoryCommand *mem_cmd = new MemoryCommand(this->mem, 0x01);
    mem_cmd->addr = addr;
    mem_cmd->result_values = values;
    mem_cmd->n = n;

    // Set this computer's status to waiting
    this->waiting_for = (Command*) mem_cmd;
}

void Computer::Computer::execute_software() {
    // Only execute an instruction if allowed from the clockspeed
    if (std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - this->last_clock_cycle).count() < this->cpu->info.clocktime) {
        return;
    }

    // Advance the timer
    this->last_clock_cycle += std::chrono::nanoseconds{this->cpu->info.clocktime};

    // Check if we're waiting
    if (this->waiting_for == NULL) {
        // Execute the next instruction
        this->cpu->execute();
    } else {
        // Check if the waiting_for is done now
        if (this->waiting_for->ready) {
            // It is, resume execution for the command
            this->cpu->execute();
            // Clear the command afterwards
            delete this->waiting_for;
            this->waiting_for = NULL;
        }
        // Otherwise, we have to wait for the hardware thread to handle it; return
    }
}
void Computer::Computer::execute_hardware() {
    // Check if there is a command waiting
    if (this->waiting_for == NULL || this->waiting_for->ready == true) {
        // Nothing to do
        return;
    }

    // Run the command on the specified hardware
    HardwareComponent *component = this->waiting_for->component;
    component->_execute_hardware(this->waiting_for);
    
    // Set the command's status
    this->waiting_for->ready = true;
}
