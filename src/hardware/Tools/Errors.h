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

    class ExecutionException : public HardwareException {
        public:
            const char instruction;
            ExecutionException(const std::string component, const std::string msg, char command)
                : HardwareException(component, msg),
                instruction(command)
            {}
    };

    class UnknownInstructionException : public ExecutionException {
        public:
            UnknownInstructionException(const char instruction, const std::string component)
                : ExecutionException(component, "Unknown instruction \"" + std::to_string(instruction) + "\"", instruction)
            {}
    };

    class MemoryException : public HardwareException {
        public:
            MemoryException(const std::string msg)
                : HardwareException("Memory", msg)
            {}
    };

    class RegistryException : public MemoryException {
        public:
            /* Exception for when the user masks invalidly on the registers */
            RegistryException(const int n)
                : MemoryException("Can only mask registers with 1, 2 or 4; not " + std::to_string(n))
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
}

#endif