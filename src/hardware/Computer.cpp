/* COMPUTER.cpp
*    by tHE iNCREDIBLE mACHINE
*
*  This file is the overarching file for the Computer. It is where components
*  are installed and communication between them happens. Currently, there is
*  only one computer, but there might be more different configurations in the
*  future.
**/

#include <iostream>
#include <fstream>
#include "../../include/Errors.h"
#include "Computer.h"

#define EEPROM_FILE "eeprom"

using namespace std;
using namespace Computer;

Computer::Computer::Computer(CPUModel cpu_model, long mem_size, int n_drives, long *drive_sizes, int n_components, PCI **pci_components)
    :n_drives(n_drives),
    n_pci(n_components)
{
    cout << endl << ">>> COMPUTER BIOS v1.0.0" << endl << endl;

    // Store the CPU
    this->cpu = new CPU(cpu_model, this);

    // Create the memory with given size
    this->mem = new Memory(mem_size);

    // Create harddrives according to the given sizes
    cout << ">>> Installing " << n_drives << " hard drives..." << endl;
    this->drives = new HardDrive*[this->n_drives];
    for (int i = 0; i < n_drives; i++) {
        this->drives[i] = new HardDrive();
    }
    cout << ">>> Done";

    // Set the given PCI Components
    cout << ">>> Installing " << n_components << " PCI Components..." << endl;
    this->components = new PCI*[this->n_pci];
    for (int i = 0; i < n_components; i++) {
        this->components[i] = pci_components[i];
    }
    cout << ">>> Done";

    // Load the EEPROM into memory
    cout << ">>> Loading EEPROM..." << endl;

    std::ifstream eeprom_file(EEPROM_FILE, ios::in | ios::binary);
    if (!eeprom_file.is_open()) {
        // Couldn't open it for some reason
        throw EEPROMException(EEPROM_FILE);
    }

    // Read all bytes and put them into the first N bytes of memory
    char buffer[100];
    int i;
    for (i = 0; i < this->mem->size;) {
        // Read 100 bytes
        int to_copy = 100;
        if (!eeprom_file.read(buffer, to_copy)) {
            // Update the number of read bytes
            to_copy = eeprom_file.gcount();
        }
        // Copy the data to memory
        this->mem->write(i, buffer, to_copy);
        // Increment i to advance
        i += to_copy;
        if (!eeprom_file) {
            // Stop, as this was likely the last bit of code
            break;
        }
    }
    cout << ">>> Done (read " << i << " bytes)" << endl;

    cout << ">>> Finilizing..." << endl;
    this->waiting_for = NULL;
    this->last_clock_cycle = chrono::high_resolution_clock::now();

    cout << ">>> BIOS booted" << endl;
}
Computer::Computer::~Computer() {
    cout << ">>> BIOS: Cleaning up..." << endl;

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

    // Also clean the waiting command if there is one
    if (this->waiting_for != NULL) {
        delete this->waiting_for;
    }

    cout << ">>> BIOS: Done." << endl;
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
    if (chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - this->last_clock_cycle).count() < this->cpu->info.clocktime) {
        return;
    }

    // Advance the timer
    this->last_clock_cycle += chrono::nanoseconds{this->cpu->info.clocktime};

    // Check if we're waiting
    if (this->waiting_for == NULL) {
        // Execute the next instruction
        this->cpu->execute();
    } else if (this->waiting_for->ready) {
        // We are, store the pointer so it isn't overwritten by accident
        Command *cmd = this->waiting_for;

        // Now resume execution
        this->cpu->execute();

        // Check if the command has been replaced by a new one
        if (this->waiting_for == cmd) {
            // It hasn't: clear the waiting_for
            this->waiting_for = NULL;
        }

        // In any case, remove the old command
        delete cmd;
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
    
    // Update the command's status
    this->waiting_for->ready = true;
}
