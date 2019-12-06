/* TYPES.g
*    by tHE iNCREDIBLE mACHINE
*
*  A file that contains general type definitions and constants for the computer.
**/

#ifndef TYPES_H
#define TYPES_H

#include <map>

namespace Computer {
    const int POINTER_REG = -1;
    const int POINTER_EEPROM = -65552;
    const int POINTER_EEPROM_SIZE = 65536;
    const int POINTER_MAX = 0x7FFFFFFF;
    /* Pointer type. 0-POINTER_MAX are valid memory addresses. Anything below zero is special:
        *   -1 t/m -16: registers
        *   -17 t/m -65552: 64 KB hardware EEPROM */
    typedef int pointer;
}

#endif