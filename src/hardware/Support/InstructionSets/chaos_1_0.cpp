/* CHAOS v1.0 INSTRUCTION SET
*    by Lut99
*
*  The simplest and earliest instruction set out there. Able to perform a
*  simple list of additions, substractions, and memory reads and writes.
**/

#include "chaos_1_0.h"

using namespace Computer;
using namespace Chaos1_0;

Instruction Chaos1_0::Set::get_instr(char command) const {

}
const std::string Chaos1_0::Set::get_name() const {
    return "Chaos";
}
const Version Chaos1_0::Set::get_version() const {
    return Version(1, 0, 0);
}

/* INSTRUCTIONS */


/* MAPS */
