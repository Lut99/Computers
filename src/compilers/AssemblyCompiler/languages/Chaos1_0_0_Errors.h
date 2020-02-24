/* CHAOS 1 0 0 ERRORS.h
 *   by Anonymous
 *
 * Created:
 *   1/15/2020, 5:15:20 PM
 * Last edited:
 *   1/16/2020, 12:00:41 PM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   This file describes errors for the Chaos Assembly Language v1.0.0.
 *   They all derive from ParseError() in the more general CompilerErrors
 *   file.
**/


#ifndef CHAOS_1_0_0_ERRORS_H
#define CHAOS_1_0_0_ERRORS_H

#include "../CompilerErrors.h"

namespace Compiler {
    class RegisterParseException: public ParseException {
        public:
            const std::string reg;

            /* Exception for when the register couldn't be parsed because '$reg' or '<reg' is missing */
            RegisterParseException(const std::string unparsable_reg)
                : ParseException("RegisterParseException", "Couldn't parse \"" + unparsable_reg + "\" as register; has to be in the form of '$regX', where X is the desired register."),
                reg(unparsable_reg)
            {}
    };

    class RegisterOutOfBoundsException: public ParseException {
        public:
            const char reg;

            /* Exception for when a register number is too large (n < 0 || n ? 15). */
            RegisterOutOfBoundsException(const char reg_out_of_bounds)
                : ParseException("RegisterOutOfBoundsException", "Register pointer " + std::to_string(reg_out_of_bounds) + " is out of bounds (0 <= reg <= 15)"),
                reg(reg_out_of_bounds)
            {}
    };

    class InvalidMemoryShortcutException: public ParseException {
        public:
            const std::string instruction;

            /* Exception for when the destination register is using a memory shortcut. */
            InvalidMemoryShortcutException(const std::string instr)
                : ParseException("InvalidMemoryShortcutException", "The \"" + instr + "\"-instruction forbids memory shortcuts ('<regX') as destination register"),
                instruction(instr)
            {}
    };

    class InvalidArgumentsException: public ParseException {
        public:
            const std::string usage;

            /* Exception for when a given instruction doesn't have the proper number of arguments or the arguments are of the wrong type */
            InvalidArgumentsException(const std::string usage_message)
                : ParseException("InvalidArgumentsException", "Invalid arguments (usage: " + usage_message + ")"),
                usage(usage_message)
            {}
    };
}

#endif