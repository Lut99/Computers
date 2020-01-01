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
    this->start_writeable = 0;
    this->is_empty = true;
}
template <class T> Buffer<T>::~Buffer() {
    delete[] this->buffer;
}

template <class T> bool Buffer<T>::write(T elem) {
    if (!this->can_write()) {
        return false;
    }

    // Fetch the writing position
    std::size_t write_i = this->end_readable.load();

    // Write to that zone
    this->buffer[write_i % this->size] = elem;
    std::cout << "Written to: " << (write_i % this->size) << std::endl;

    // Update the readable var
    this->end_readable.store(write_i + 1);

    return true;
}
template <class T> bool Buffer<T>::can_write() const {
    // Only returns true if:
    //   - (start_writeable - start_readable) >= 0 && (end_readable - start_readable) <= size
    //   - (start_writeable - start_readable) < 0 && (end_readable + (size - start_readable)) <= size
    std::size_t start = this->start_readable.load();
    std::size_t end = this->end_readable.load();
    return (end - start >= 0 && end - start < this->size) || (end - start < 0 && end + (this->size - start) < this->size);
}

template <class T> bool Buffer<T>::read(T& elem) {
    if (!this->can_read()) {
        return false;
    }

    // Read from the start of the zone
    std::size_t read_i = this->start_readable.load();
    elem = this->buffer[read_i % this->size];
    
    //std::cout << "Read from: " << (read_i % this->size) << std::endl;

    // Update the readable var
    this->start_readable.store(read_i + 1);

    return true;
}
template <class T> bool Buffer<T>::can_read() const {
    // Only returns true if:
    //   - end_readable != start_readable
    std::size_t start = this->start_readable.load();
    std::size_t end = this->end_readable.load();
    return start != end;
}

template <class T> std::string Buffer<T>::to_string() const {
    const static int bar_length = 50;

    std::size_t start = this->start_readable.load();
    std::size_t end = this->end_readable.load();

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