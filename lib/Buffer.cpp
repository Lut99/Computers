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
    this->start_readable.store(0);
    this->start_writeable.store(0);
    this->is_empty.store(true);
}
template <class T> Buffer<T>::~Buffer() {
    delete[] this->buffer;
}

template <class T> bool Buffer<T>::write(T elem) {
    if (!this->can_write()) {
        return false;
    }

    // Write to the start of the writeable zone
    std::size_t write_i = this->start_writeable.load();
    this->buffer[write_i] = elem;

    // Update the writable var
    write_i++;
    if (write_i >= this->size) {
        write_i = 0;
    }
    this->start_writeable.store(write_i);

    // The buffer isn't empty by default
    this->is_empty.store(false);

    return true;
}
template <class T> bool Buffer<T>::can_write() const {
    // Only returns true if:
    //   - (start_writeable - start_readable) >= 0 && (end_readable - start_readable) <= size
    //   - (start_writeable - start_readable) < 0 && (end_readable + (size - start_readable)) <= size
    std::size_t start = this->start_readable.load();
    std::size_t end = this->start_writeable.load();
    bool empty = this->is_empty.load();
    return empty || start != end;
}

template <class T> bool Buffer<T>::read(T& elem) {
    if (!this->can_read()) {
        return false;
    }

    // Read from the start of the zone
    std::size_t read_i = this->start_readable.load();
    elem = this->buffer[read_i];

    // Update the readable var
    read_i++;
    if (read_i >= this->size) {
        read_i = 0;
    }
    this->start_readable.store(read_i);

    // If now start_readable == start_writeable, then update empty to being true
    if (read_i == this->start_writeable.load()) {
        this->is_empty.store(true);
    }

    return true;
}
template <class T> bool Buffer<T>::can_read() const {
    // Only returns true if:
    //   - end_readable != start_readable
    std::size_t empty = this->is_empty.load();
    return !empty;
}

template <class T> std::string Buffer<T>::to_string() const {
    const static int bar_length = 50;

    std::size_t start = this->start_readable.load();
    std::size_t end = this->start_writeable.load();
    std::size_t empty = this->is_empty.load();

    // First, compute the pixel posses
    int start_pos = (int) (((start / (float) this->size) * bar_length) + 0.5);
    int end_pos = (int) (((end / (float) this->size) * bar_length) + 0.5);

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
    if (empty) {
        bar_line << " (empty)";
    }
    bar_line << std::endl;
    end_line << " (end = " << end << ")" << std::endl;
    
    // return
    return start_line.str() + bar_line.str() + end_line.str();
}