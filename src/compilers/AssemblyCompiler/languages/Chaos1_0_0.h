/* CHAOS v1.0 INSTRUCTION SET COMPILER (header file)
*    by Lut99
*
*  A header file for Chaos1_0.cpp.
**/

#ifndef CHAOS1_0_0_H
#define CHAOS1_0_0_H

#include "../../../include/Array.h"
#include "../AssemblyCompiler.h"

namespace Compiler {
    class Chaos1_0_0_compiler : public AssemblyCompiler {
        private:
            /* Compile functions for specific operators. */

            /* Compiles the ADD-instruction. */
            void Compile_ADD(DataTypes::BinaryStream& result, DataTypes::Array<string> args);

            /* Compiles the MEM_READ-instruction. */
            void Compile_MEM_READ(DataTypes::BinaryStream& result, DataTypes::Array<string> args);


        public:
            /* The Chaos1_0_0 compiler is a derivative from the default AssemblyCompiler class. They idea is for every line in the preparsed input file, it takes that line and returns a binary string that can be written to the output file. */
            Chaos1_0_0_compiler();

            /* The assemble step of the pipeline. Takes a line from the file, determines what the correct operator is and outputs a the result in the given binarystream. Note that this function should be allowed to throw errors by itself (non-catchable). */
            void compile(DataTypes::BinaryStream& result, std::string command, DataTypes::Array<std::string> args);
    };

    /* Creates and returns a pointer to the derived AssemblyCompiler class. Be aware that this should be deleted. */
    AssemblyCompiler *compiler_factory();
}

#endif