/* BUFFER.cpp
*    by Lut99
*
*  A class that can act as a thread-safe buffer between two threads in a
*  pipeline. It is designed in such a way that one thread writes to the
*  buffer, and one reads from it.
**/

#include <iostream>
#include <sstream>
#include <limits.h>

#include "../include/Buffer.h"

using namespace DataTypes;

template <class T> Buffer<T>::Buffer(std::size_t size)
    :size(size)
{
    // Create a buffer of the appropriate type and size
    this->buffer = new T[this->size];

    // Set the i's to zero.
    this->start_readable = 0;
    this->end_readable = 0;
}
template <class T> Buffer<T>::~Buffer() {
    delete[] this->buffer;
}

template <class T> bool Buffer<T>::write(T elem) {
    if (!this->can_write()) {
        return false;
    }

    // Increment end_readable
    std::size_t to_write = this->end_readable + 1;

    // Write to that zone
    this->buffer[to_write % this->size] = elem;

    // Update the readable var
    this->end_readable = to_write;

    return true;
}
template <class T> bool Buffer<T>::can_write() const {
    // Only returns true if:
    //   - (end_readable - start_readable) >= 0 && (end_readable - start_readable) <= size
    //   - (end_readable - start_readable) < 0 && (end_readable + (size - start_readable)) <= size
    std::size_t start = this->start_readable;
    std::size_t end = this->end_readable;
    return (end - start >= 0 && end - start < this->size) || (end - start < 0 && end + (this->size - start) < this->size);
}

template <class T> bool Buffer<T>::read(T& elem) {
    if (!this->can_read()) {
        return false;
    }

    // Read from the start of the zone
    elem = this->buffer[this->start_readable % this->size];

    // Update the readable var
    this->start_readable++;

    return true;
}
template <class T> bool Buffer<T>::can_read() const {
    // Only returns true if:
    //   - end_readable != start_readable
    std::size_t start = this->start_readable;
    std::size_t end = this->end_readable;
    return start != end;
}

template <class T> std::string Buffer<T>::to_string() const {
    const static int bar_length = 50;

    std::size_t start = this->start_readable;
    std::size_t end = this->end_readable;

    // First, compute the pixel posses
    int start_pos = (int) ((((start % this->size) / (float) this->size) * bar_length) + 0.5);
    int end_pos = (int) ((((end % this->size) / (float) this->size) * bar_length) + 0.5);

    // Next, print the three lines
    std::stringstream start_line;
    std::stringstream bar_line;
    std::stringstream end_line;
    for (int i = 0; i < bar_length; i++) {
        if (i == start_pos) {
            start_line << 'v';
        } else {
            start_line << ' ';
        }

        bar_line << '=';

        if (i == end_pos) {
            end_line << '^';
        } else {
            end_line << ' ';
        }
    }
    // Add other text + newlines
    start_line << " (start = " << start << ")" << std::endl;
    bar_line << std::endl;
    end_line << " (end = " << end << ")" << std::endl;
    
    // return
    return start_line.str() + bar_line.str() + end_line.str();
}