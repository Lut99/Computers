/* SCANNER EXCEPTIONS.hpp
 *   by Lut99
 *
 * Created:
 *   3/23/2020, 1:00:41 PM
 * Last edited:
 *   3/26/2020, 5:09:46 PM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   This file contains all exceptions for the Scanner.
**/

#ifndef SCANNEREXCEPTIONS_HPP
#define SCANNEREXCEPTIONS_HPP

#include <exception>
#include <string>
#include <cstring>
#include <cerrno>

namespace Assembler {
    class AssemblerException: public std::exception {
        public:
            const unsigned long line;
            const unsigned long col;
            const std::string msg;

            /* Base exception for all Assembler-related exceptions. */
            AssemblerException(const unsigned long line_number, const unsigned long col_number, const std::string message)
                : exception(),
                line(line_number),
                col(col_number),
                msg(message)
            {}

            /* Returns a message with what went wrong. */
            virtual const char* what() const throw() {
                return this->msg.c_str();
            }
    };



    class FileReadException: public AssemblerException {
        public:
            const error_t error_no;

            /* Exception for when the file couldn't be read. */
            FileReadException(const unsigned long line_number, const unsigned long col_number, const error_t errornumber)
                : AssemblerException(line_number, col_number,
                                     std::string("Could not read from file: ") + std::string(strerror(errornumber))),
                error_no(errornumber)
            {}
    };



    class SyntaxError: public AssemblerException {
        public:
            const std::string text;

            /* Exception for when the file couldn't be read. */
            SyntaxError(const unsigned long line_number, const unsigned long col_number, const std::string scanned_text)
                : AssemblerException(line_number, col_number, std::string("Syntax error: ") + scanned_text),
                text(scanned_text)
            {}
    };

    class OverflowError: public SyntaxError {
        public:
            /* Exception for when a constant is too large. */
            OverflowError(const unsigned long line_number, const unsigned long col_number, const std::string scanned_text)
                : SyntaxError(line_number, col_number, scanned_text)
            {}
    };

    class DecOverflowError: public OverflowError {
        public:
            /* Special case exception for when a decimal constant is too large. */
            DecOverflowError(const unsigned long line_number, const unsigned long col_number, const std::string scanned_text)
                : OverflowError(line_number, col_number, scanned_text)
            {}
    };

    class HexOverflowError: public OverflowError {
        public:
            /* Special case exception for when a hex constant is too large. */
            HexOverflowError(const unsigned long line_number, const unsigned long col_number, const std::string scanned_text)
                : OverflowError(line_number, col_number, scanned_text)
            {}
    };

    class RegOverflowError: public OverflowError {
        public:
            /* Special case exception for when a register constant is too large. */
            RegOverflowError(const unsigned long line_number, const unsigned long col_number, const std::string scanned_text)
                : OverflowError(line_number, col_number, scanned_text)
            {}
    };
}

#endif