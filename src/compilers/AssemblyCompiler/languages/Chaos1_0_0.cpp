/* CHAOS v1.0 INSTRUCTION SET COMPILER
*    by Lut99
*
*  A subfile for ChaosCompiler, that can compile a given instruction to binary
*  code.
**/

#include <iostream>
#include <sstream>
#include <string>

#include "../../../include/StringConverter.h"
#include "../CompilerErrors.h"
#include "Chaos1_0_0_Errors.h"
#include "Chaos1_0_0.h"

using namespace std;
using namespace Compiler;
using namespace DataTypes;

/* This struct not only stores a register pointer, but also whether the pointer to that register is a memory varient or not. */
struct Register {
    char pointer;
    bool is_mem;
};


/* PARSE TOOLS */
void parse_reg(Register& result, string raw) {
    // First, check if the first bit is either '$' or '>'
    const char *raw_raw = raw.c_str();
    if (raw.length() < 5 || (raw_raw[0] != '$' && raw_raw[0] != '<')) {
        throw RegisterParseException(raw);
    }

    // Then, check if what comes after is 'reg'
    if (raw.substr(1, 3) != "reg") {
        throw RegisterParseException(raw);
    }

    // Now that it's valid, parse the remaining characters as number
    string num_raw = raw.substr(4);
    char num;
    try {
        num = StringConverter::toInteger<char>(raw.substr(4));
    } catch (StringConverter::StringConvertionException& e) {
        // Re-cast as ParseError
        throw RegisterParseException(raw);
    }

    // Check if it is within bounds
    if (num < 0 || num > 15) {
        throw RegisterOutOfBoundsException(num);
    }

    // Everything checks out; return
    result.pointer = num;
    result.is_mem = raw_raw[0] == '<';
}


/* INSTRUCTION COMPILERS */
void Compile_ADD(BinaryStream& result, Array<string> args) {
    // Parse the first and second registers
    Register des_reg, val_reg;
    parse_reg(des_reg, args[0]);
    parse_reg(val_reg, args[1]);

    // Make sure the first one isn't a memory one
    if (des_reg.is_mem) {
        throw InvalidMemoryShortcutException("ADD");
    }

    // If the second one is a memory one, first add a MEM_READ
    if (val_reg.is_mem) {
        Compile_MEM_READ(result, Array<string>() {});
    }
}

void Compile_MEM_READ(BinaryStream& result, Array<string> args) {

}


Chaos1_0_0_compiler::Chaos1_0_0_compiler()
    : AssemblyCompiler("Chaos Assembly Language v1.0.0 Compiler", "Chaos1_0_0")
{}

void Chaos1_0_0_compiler::compile(DataTypes::BinaryStream& result, std::string command, Array<std::string> args) {
    // Determine the proper compile function for that command
    if (command == "add") {
        Compile_ADD(result, args);
    } else {
        throw UnknownInstructionException(command);
    }
}

AssemblyCompiler *Compiler::compiler_factory() {
    return new Chaos1_0_0_compiler();
}
