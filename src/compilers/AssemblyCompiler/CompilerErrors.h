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
            const std::string msg;
            const std::size_t line;
            const std::string filepath;

            /* Base exception class for all parse errors */
            ParseException(const std::size_t errored_line, const std::string path, const std::string message)
                : line(errored_line),
                filepath(path),
                msg(path + " Line " + std::to_string(line) + ": " + message)
            {}
    };

    class UnknownInstructionException : public ParseException {
        public:
            const std::string instruction;

            /* Exception for when the compiler encounters an instruction it does not know */
            UnknownInstructionException(const std::size_t errored_line, const std::string path, const std::string instr)
                : ParseException(errored_line, path, "Unknown instruction \"" + instr + "\""),
                instruction(instr)
            {}
    };
}

#endif