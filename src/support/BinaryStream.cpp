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

#include <limits.h>

#include "BinaryStream.h"

using namespace std;
using namespace DataTypes;

/* BINARY STRINGS */
BinaryString::BinaryString(char *data_string, std::size_t data_size) {
    // Simply set these as values
    this->data = data_string;
    this->size = data_size;
}
BinaryString::BinaryString(void *data_string, std::size_t data_size) {
    // Reinterpret cast the void*
    this->data = static_cast<char*>(data_string);
    this->size = data_size;
}
BinaryString::BinaryString(char *null_terminated_string) {
    // Set the values
    this->data = null_terminated_string;
    this->size = 0;
    // Now loop and find the size
    for (; this->size < INT_MAX; this->size++) {
        // Stop if the '\0'is found
        if (null_terminated_string[this->size] == '\0') {
            break;
        }
    }
    // Add an additional count for '\0' itself
    this->size++;
}

/* BINARY STREAM */
BinaryStream::BinaryStream(std::size_t initial_size=256) {
    this->size = 0;
    this->init_size = initial_size;
    this->real_size = initial_size;
    this->binary_string = new char[this->real_size];
}
BinaryStream::~BinaryStream() {
    delete[] this->binary_string;
}

const std::size_t BinaryStream::read(char *result) const {
    // Copy this->size elements to the other array and return the amount copied
    for (std::size_t i = 0; i < this->size; i++) {
        result[i] = this->binary_string[i];
    }
    return this->size;
}
const std::size_t BinaryStream::flush(char *result) {
    // Copy this->size elements to the other array and return the amount copied
    for (std::size_t i = 0; i < this->size; i++) {
        result[i] = this->binary_string[i];
    }
    std::size_t to_return = this->size;

    // Before returning, reset the buffer
    this->clear();

    return to_return;
}

const std::size_t BinaryStream::length() const {
    return this->size;
}

void BinaryStream::clear() {
    delete[] this->binary_string;
    this->size = 0;
    this->real_size = this->init_size;
    this->binary_string = new char[this->real_size];
}

/* STREAM OPERATORS */
BinaryStream& DataTypes::operator<<(BinaryStream& bs, const unsigned char value) {
    // Re-interpret cast to char, then add to the stream
    char data[1];
    data[0] = (char) value;
    bs.append(data, 1);
}