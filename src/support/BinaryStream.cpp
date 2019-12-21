/* BINARY STREAM.cpp
*    by Lut99
*
*  This file is used to make writing binary strings easier. It functions
*  similar to a StringStream, with the exception that it parses datatypes to
*  character arrays and appending those to an internal one, using among others
*  Encoding.h. If desired, a specific stream operator '<<' can be implemented
*  by making use of the classes' ".append()" function, which appends a given
*  character array to the internal one.
**/

#include "BinaryStream.h"
