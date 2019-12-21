/* CHAOS v1.0 INSTRUCTION SET COMPILER (header file)
*    by Lut99
*
*  A header file for Chaos1_0.cpp.
**/

#ifndef CHAOS1_0_H
#define CHAOS1_0_H

#include "AssemblyCompiler.h"

namespace Compiler {
    class Chaos1_0_0_compiler : AssemblyCompiler {
        public:
            /* The Chaos1_0_0 compiler is a derivative from the default AssemblyCompiler class. They idea is for every line in the preparsed input file, it takes that line and returns a binary string that can be written to the output file. */
            Chaos1_0_0_compiler();
    };
}

#endif