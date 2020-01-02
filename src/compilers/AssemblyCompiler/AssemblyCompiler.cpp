/* ASSEMBLY COMPILER.cpp
*    by Lut99
*
*  A baseclass for all assembly-based compilers. All they have to implement
*  are functions that take a text-based string representing one line from the
*  input file and output a BinaryString object, that can then easily be written
*  back to a file.
**/

#include "../../include/Errors.h"
#include "AssemblyCompiler.h"

using namespace Compiler;

AssemblyCompiler::AssemblyCompiler(std::string compiler_name, std::string compiler_id)
    : name(compiler_name),
    id(compiler_id)
{}

void AssemblyCompiler::compile(DataTypes::BinaryStream& result, std::string command, DataTypes::Array<std::string> args) {
    // Throw not-implemented error
    throw Computer::NoOverrideException("AssemblyCompiler::compile");
}
