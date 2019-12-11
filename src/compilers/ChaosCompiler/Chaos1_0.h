/* CHAOS v1.0 INSTRUCTION SET COMPILER (header file)
*    by Lut99
*
*  A header file for Chaos1_0.cpp.
**/

#ifndef CHAOS1_0_H
#define CHAOS1_0_H

#include <fstream>

namespace Compiler {
    namespace Chaos {
        /* Parses a given filestream as if it was Chaos v1.0.0 Assembly Language. The given output stream is where the result will be written to, and if verbose is given, the compiler reports it's progress. */
        void parse_chaos_1_0_0(std::ifstream& preparsed_file, std::ofstream& output_file, bool verbose);
    }
}

#endif