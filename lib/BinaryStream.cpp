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

#include <iostream>
#include <sstream>
#include <limits.h>

#include "../include/Encoding.h"
#include "../include/BinaryStream.h"

#define RESIZE_FACTOR 1.5

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
BinaryStream::BinaryStream(std::size_t initial_size) {
    this->size = 0;
    this->init_size = initial_size;
    this->real_size = initial_size;
    this->binary_string = new char[this->real_size];
}
BinaryStream::~BinaryStream() {
    delete[] this->binary_string;
}

void BinaryStream::append(const char *data, const std::size_t n) {
    // STEP 1: Resize to the new value. Note that this throws an error if
    //         memory allocation is not possible.
    while (this->size + n > this->real_size) {
        // Allocate new memory space
        std::size_t new_real_size = (std::size_t) (this->real_size * RESIZE_FACTOR);
        char *new_binary_string = new char[new_real_size];

        // Copy the contents to the new string
        for (int i = 0; i < this->size; i++) {
            new_binary_string[i] = this->binary_string[i];
        }

        // Deallocate the old stuff and overwrite with new
        delete[] this->binary_string;
        this->binary_string = new_binary_string;
        this->real_size = new_real_size;
    }

    // STEP 2: Copy the contents to the internal array
    for (int i = 0; i < n; i++) {
        this->binary_string[this->size + i] = data[i];
    }

    // STEP 3: Update the size variable
    this->size += n;
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

std::string BinaryStream::to_string() {
    stringstream sstr;
    sstr << "[";
    for (std::size_t i = 0; i < this->size; i++) {
        if (i > 0) {
            sstr << ",";
        }
        sstr << ((int) this->binary_string[i]);
    }
    sstr << "]";
    return sstr.str();
}

/* ADD OVERLOADS */
BinaryStream& BinaryStream::add(const unsigned char value) {
    // Re-interpret cast to char, then add to the stream
    char data[1];
    Enc::encode(data, value);
    this->append(data, 1);
    return *this;
}
BinaryStream& BinaryStream::add(const int value) {
    // Make use of Encoding.h to covert this to a binary string
    char data[4];
    Enc::encode(data, value);
    this->append(data, 4);
    return *this;
}
BinaryStream& BinaryStream::add(const char *value) {
    // Count how many elements are in this zero-terminated string
    std::size_t count = 1;
    for (; value[count] != '\0'; count++) {}
    this->append(value, count);
    return *this;
}
BinaryStream& BinaryStream::add(const std::string value) {
    // Append the inner string
    this->append(value.c_str(), value.length());
    return *this;
}

/* STREAM OPERATORS */

BinaryStream& DataTypes::operator<<(BinaryStream& bs, const unsigned char value) {
    // Re-interpret cast to char, then add to the stream
    char data[1];
    data[0] = (char) value;
    bs.append(data, 1);
    return bs;
}
BinaryStream& DataTypes::operator<<(BinaryStream& bs, const char value) {
    // No need to do anything, just append it
    bs.append(&value, 1);
    return bs;
}
BinaryStream& DataTypes::operator<<(BinaryStream& bs, const unsigned short value) {
    // Make use of Encoding.h to covert this to a binary string
    char data[2];
    Enc::encode(data, value);
    bs.append(data, 2);
    return bs;
}
BinaryStream& DataTypes::operator<<(BinaryStream& bs, const short value) {
    // Make use of Encoding.h to covert this to a binary string
    char data[2];
    Enc::encode(data, value);
    bs.append(data, 2);
    return bs;
}
BinaryStream& DataTypes::operator<<(BinaryStream& bs, const unsigned int value) {
    // Make use of Encoding.h to covert this to a binary string
    char data[4];
    Enc::encode(data, value);
    bs.append(data, 4);
    return bs;
}
BinaryStream& DataTypes::operator<<(BinaryStream& bs, const int value) {
    // Make use of Encoding.h to covert this to a binary string
    char data[4];
    Enc::encode(data, value);
    bs.append(data, 4);
    return bs;
}
BinaryStream& DataTypes::operator<<(BinaryStream& bs, const unsigned long value) {
    // Make use of Encoding.h to covert this to a binary string
    char data[8];
    Enc::encode(data, value);
    bs.append(data, 8);
    return bs;
}
BinaryStream& DataTypes::operator<<(BinaryStream& bs, const long value) {
    // Make use of Encoding.h to covert this to a binary string
    char data[8];
    Enc::encode(data, value);
    bs.append(data, 8);
    return bs;
}
BinaryStream& DataTypes::operator<<(BinaryStream& bs, const char *value) {
    // Count how many elements are in this zero-terminated string
    std::size_t count = 1;
    for (; value[count] != '\0'; count++) {}
    bs.append(value, count);
    return bs;
}
BinaryStream& DataTypes::operator<<(BinaryStream& bs, const std::string value) {
    // Append the inner string
    bs.append(value.c_str(), value.length());
    return bs;
}
BinaryStream& DataTypes::operator<<(BinaryStream& bs, const BinaryString value) {
    // Append the binary string's characters
    bs.append(value.data, value.size);
    return bs;
}
BinaryStream& DataTypes::operator<<(BinaryStream& bs, const BinaryStream value) {
    // Append the second stream's contents to the first
    bs.append(value.binary_string, value.size);
    return bs;
}
std::ostream& DataTypes::operator<<(std::ostream& os, const BinaryStream bs) {
    // Append each character of the bs array
    for (int i = 0; i < bs.length(); i++) {
        os << bs.binary_string[i];
    }
    return os;
}