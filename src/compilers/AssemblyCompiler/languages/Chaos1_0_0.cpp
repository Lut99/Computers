/* CHAOS v1.0 INSTRUCTION SET COMPILER
*    by Lut99
*
*  A subfile for ChaosCompiler, that can compile a given instruction to binary
*  code.
**/

#include <iostream>
#include <sstream>
#include <string>

#include "../CompilerErrors.h"
#include "Chaos1_0_0.h"

using namespace std;
using namespace Compiler;
using namespace DataTypes;

/* TOOLS */


Chaos1_0_0_compiler::Chaos1_0_0_compiler()
    : AssemblyCompiler("Chaos Assembly Language v1.0.0 Compiler", "Chaos1_0_0")
{}

void Chaos1_0_0_compiler::compile(DataTypes::BinaryStream& result, std::string command, DataTypes::Array<std::string> args) {
    // Determine the proper compile function for that command
    if (command == "add") {
        
    } else {
        throw UnknownInstructionException(line_number, this->filepath, command);
    }
}

AssemblyCompiler *Compiler::compiler_factory() {
    return new Chaos1_0_0_compiler();
}
