/* CHAOS v1.0 INSTRUCTION SET COMPILER (header file)
*    by Lut99
*
*  A header file for Chaos1_0.cpp.
**/

#ifndef CHAOS1_0_H
#define CHAOS1_0_H

#include <map>
#include <fstream>

namespace Compiler {
    namespace Chaos {
        /* Map type for the id-to-func mapper */
        typedef std::map<std::string, std::string(*)(std::string *args, std::ofstream& output_file)> idmap;

        /* Maps instruction identifiers to their respective parsers. If the parse function returns anything else than an empty string, it is an error message. */
        static idmap INSTRUCTION_MAP;

        /* Parses a given filestream as if it was Chaos v1.0.0 Assembly Language. The given output stream is where the result will be written to, and if verbose is given, the compiler reports it's progress. */
        void parse_chaos_1_0_0(std::ifstream& preparsed_file, std::ofstream& output_file, bool verbose);
    }
}

#endif