/* ERRORS.h
*    by tHE iNCREDIBLE mACHINE
*
*  Header file for Errors.cpp
**/

#ifndef ERRORS_H
#define ERRORS_H

#include <exception>
#include <string>
#include "Types.h"

namespace Computer {
    class HardwareException : public std::exception {
        public:
            const std::string component;
            const std::string msg;
            HardwareException(const std::string component, const std::string msg)
                : std::exception(),
                component(component),
                msg(msg)
            {}
    };

    class NoOverrideException : public HardwareException {
        public:
            /* Exception for when a virtual class isn't overridden */
            NoOverrideException(const std::string func_name)
                : HardwareException("unknown", "Function \"" + func_name + "\" isn't overridden by child class.")
            {}
    };

    class ComponentException : public HardwareException {
        public:
            /* Base exception for Component related exceptions */
            ComponentException(const std::string component_name, const std::string msg)
                : HardwareException(component_name, component_name + ": " + msg)
            {}
    };
    class UnknownCommandException : public ComponentException {
        public:
            /* Exception for when an unknown command is tried to be executed on a Hardware Component */
            UnknownCommandException(const char command_id, const std::string component_name)
                : ComponentException(component_name, "Command " + std::to_string(command_id) + " unknown")
            {}
    };
    class UnknownIdException : public ComponentException {
        public:
            /* Exception for when an unknown id is tried to be accessed in a queue on Hardware Component */
            UnknownIdException(const char id, const std::string component_name)
                : ComponentException(component_name, "Command with id " + std::to_string(id) + " is not scheduled")
            {}
    };
    class CommandQueueOverflowException : public ComponentException {
        public:
            /* Exception for when too many commands are scheduled concurrently */
            CommandQueueOverflowException(const int current_size, const int max_size, const std::string component_name)
                : ComponentException(component_name, "Too many commands (" + std::to_string(current_size) + " > " + std::to_string(max_size))
            {}
    };

    class ExecutionException : public HardwareException {
        public:
            const char instruction;
            ExecutionException(const std::string msg, char command)
                : HardwareException("CPU", msg),
                instruction(command)
            {}
    };

    class UnknownInstructionException : public ExecutionException {
        public:
            UnknownInstructionException(const char instruction, const std::string instr_set_name)
                : ExecutionException("Unknown instruction \"" + std::to_string(instruction) + "\" (Instruction set: \"" + instr_set_name + "\")", instruction)
            {}
    };

    class MemoryException : public HardwareException {
        public:
            MemoryException(const std::string msg)
                : HardwareException("Memory", msg)
            {}
    };
    class MemoryOutOfBoundsException : public MemoryException {
        public:
            /* Exception for when a pointer points outside of available memory */
            MemoryOutOfBoundsException(pointer value, long maximum)
                : MemoryException(std::to_string(value) + " > " + std::to_string(maximum))
            {}
    };
    class MemoryOverflowException : public MemoryException {
        public:
            /* Exception for when more memory is written than there is space left at the end of memory */
            MemoryOverflowException(pointer start, int args_size, long maximum)
                : MemoryException(std::to_string(start) + " + " + std::to_string(args_size) + " > " + std::to_string(maximum))
            {}
    };
    class MemoryBlockMisalignmentException : public MemoryException {
        public:
            /* Exception for when the total memory size isn't dividable by the blocksize */
            MemoryBlockMisalignmentException(const long total_size, const long block_size)
                : MemoryException(std::to_string(total_size) + " isn't dividable by " + std::to_string(block_size))
            {}
    };

    class RegisterException : public MemoryException {
        public:
            const int reg;
            /* Base exception for all register exceptions */
            RegisterException(const int reg, const std::string msg)
                : reg(reg),
                MemoryException("Register " + std::to_string(reg) + ": " + msg)
            {}
    };
    class RegistryOutOfBoundsException : public RegisterException {
        public:
            /* Exception for when a non-existing register is accessed */
            RegistryOutOfBoundsException(const int accessed_reg, const int max_reg)
                : RegisterException(accessed_reg, "Does not exist, " + std::to_string(max_reg) + " is the number of registers.")
            {}
    };

    class IOException : public HardwareException {
        public:
            /* Exception base class for when an real-life IO file couldn't be opened */
            IOException(const std::string path, const std::string component)
                : HardwareException(component, "File \"" + path + "\" could not be opened")
            {}
    };
    class EEPROMException : public IOException {
        public:
            /* Exception for when the EEPROM file couldn't be opened */
            EEPROMException(const std::string path)
                : IOException(path, "Computer")
            {}
    };
}

#endif