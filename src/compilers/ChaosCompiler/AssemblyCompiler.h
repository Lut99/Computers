/* ASSEMBLY COMPILER.h
*    by Lut99
*
*  Header file for AssemblyCompiler.cpp.
**/

#ifndef ASSEMBLYCOMPILER_H
#define ASSEMBLYCOMPILER_H

#include <string>

#include "../../../include/BinaryStream.h"

namespace Compiler {
    class AssemblyCompiler {
        public:
            const std::string name;
            const std::string id;
            
            /* The baseclass for any Assembly Compiler. Note that this constructor should only be called from their derived classes. */
            AssemblyCompiler(std::string compiler_name, std::string compiler_id);

            /* The assemble step of the pipeline. Takes a line from the file, determines what the correct operator is and outputs a the result in the given binarystream. Note that this function should be allowed to throw errors by itself (non-catchable). */
            virtual void compile(DataTypes::BinaryStream& result, std::string line) const;

            /* A static factory class that can be overridden by child classes to create the proper type. Note that the compiler should be destroyed later on. */
            virtual AssemblyCompiler *get_compiler() const;
    };
}

#endif