/* HARDWARE COMPONENT.cpp
*    by Lut99
*
*  This file contains the baseclass for all hardware components, save the CPU
*  itself. This allows the Computer class to go to sleep while execution waits
*  for hardware access.
**/

#include "Support/Errors.h"
#include "HardwareComponent.h"

using namespace std;
using namespace Computer;


Command::Command(HardwareComponent *component, unsigned char operation) {
    this->component = component;
    this->operation = operation;
    this->ready = false;
}

HardwareComponent::HardwareComponent(int id, string name)
    : _id(id),
    _name(name)
{}

void HardwareComponent::_execute_hardware(Command *cmd) {
    /* Not implemented */
    throw NoOverrideException("HardwareComponent::_execute_hardware");
}
