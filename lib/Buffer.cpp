/* BUFFER.cpp
*    by Lut99
*
*  A class that can act as a thread-safe buffer between two threads in a
*  pipeline. It is designed in such a way that one thread writes to the
*  buffer, and one reads from it.
**/

#include "../include/Buffer.h"

using namespace DataTypes;

template <class T> Buffer<T>::Buffer(std::size_t size)
    :size(size)
{
    // Create a buffer of the appropriate type and size
    this->buffer = new T[this->size];

    // Set the i's to zero.
    this->next_write = 0;
    this->last_write = 0;
    this->next_read = 0;
    this->last_read = 0;
}
template <class T> Buffer<T>::~Buffer() {
    delete[] this->buffer;
}

template <class T> bool Buffer<T>::write(T elem) {
    if (!this->can_write()) {
        return false;
    }

    // Write to next_write
    this->buffer[this->next_write] = elem;

    // Update last_write to next_write, signalling the other thread to read one more
    this->last_write = this->next_write;

    // Update next_write
    std::size_t new_next_write = this->next_write + 1;
    if (new_next_write >= this->size) {
        new_next_write = 0;
    }
    this->next_write = new_next_write;

    return true;
}
template <class T> bool Buffer<T>::can_write() {
    // Only returns true if:
    //   - next_write >= next_read
    return this->next_write >= this->last_read && this->next_write <= this->next_read;
}

template <class T> bool Buffer<T>::read(T& elem) {
    if (!this->can_read()) {
        return false;
    }

    // Write from next_read
    elem = this->buffer[this->next_read];

    // Update last_read to next_read, signalling the other thread to write one more
    this->last_read = this->next_read;

    // Update next_read
    std::size_t new_next_read = this->next_read + 1;
    if (new_next_read >= this->size) {
        new_next_read = 0;
    }
    this->next_read = new_next_read;

    return true;
}
template <class T> bool Buffer<T>::can_read() {
    // Only returns true if:
    //   - next_write != next_from
    return this->next_write != this->next_read;
}