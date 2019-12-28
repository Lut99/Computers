/* CHAOS v1.0 INSTRUCTION SET COMPILER
*    by Lut99
*
*  A subfile for ChaosCompiler, that can compile a given instruction to binary
*  code.
**/

#include <string>

#include "Chaos1_0_0.h"

using namespace std;
using namespace Compiler;

Chaos1_0_0_compiler::Chaos1_0_0_compiler()
    : AssemblyCompiler("Chaos Assembly Language v1.0.0 Compiler", "Chaos1_0_0")
{}

void Chaos1_0_0_compiler::compile(DataTypes::BinaryStream& result, std::string line) {
    // For now, just return 'success' or something
    result << "success";
}

AssemblyCompiler *Compiler::compiler_factory() {
    return new Chaos1_0_0_compiler;
}
