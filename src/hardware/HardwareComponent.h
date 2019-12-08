/* HARDWARE COMPONENT.h
*    by Lut99
*
*  Header file for HardwareComponent.cpp
**/

#ifndef HARDWARECOMPONENT_H
#define HARDWARECOMPONENT_H

#include <string>
#include "Computer.h"

#define COMMAND_QUEUE_SIZE 1

namespace Computer {
    struct Command {
        HardwareComponent *component;
        unsigned char operation;
        bool ready;

        // Create a default initializer
        Command(HardwareComponent *component, unsigned char operation);
    };

    class HardwareComponent {
        protected:
            const int _id;
            const std::string _name;

            /* Baseclass for components. Shouldn't be called, except from child classes. */
            HardwareComponent(int id, std::string name);

            /* Executes the hardware part for this component for given command */
            virtual void _execute_hardware(Command *cmd);
        public:
            /* Declare the Computer class to be a friend */
            friend class Computer;
    };
}

#endif