/* COMPILER ERRORS.h
*    by Lut99
*
*  An error file for chaos_make and derived compilers.
**/

#ifndef COMPILER_ERRORS_H
#define COMPILER_ERRORS_H

#include <string>
#include <exception>

namespace Compiler {
    class ParseException : public std::exception {
        public:
            const std::string name;
            const std::string msg;

            /* Base exception class for all parse errors */
            ParseException(const std::string error_name, const std::string message)
                : name(error_name),
                msg(message)
            {}
    };

    class UnknownInstructionException : public ParseException {
        public:
            const std::string instruction;

            /* Exception for when the compiler encounters an instruction it does not know */
            UnknownInstructionException(const std::string instr)
                : ParseException("UnknownInstructionException", "Unknown instruction \"" + instr + "\""),
                instruction(instr)
            {}
    };
}

#endif