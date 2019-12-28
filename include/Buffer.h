/* BUFFER.h
*    by Lut99
*
*  Header file for Buffer.cpp.
**/

#ifndef BUFFER_H
#define BUFFER_H

#include <cstddef>

namespace DataTypes {
    template <class T> class Buffer {
        private:
            T *buffer;

            std::size_t next_write;
            std::size_t last_write;
            std::size_t next_read;
            std::size_t last_read;
        public:
            const std::size_t size;

            /* The buffer class provides a thread-safe way for one thread to push a continious stream of information to a second thread. Uses no locks whatsoever. */
            Buffer(std::size_t size);
            ~Buffer();

            /* Writes given element to the buffer. Returns true if it was successfull, or false if the buffer was full. */
            bool write(T elem);
            /* Checks whether the buffer has space for more elements. */
            bool can_write();

            /* Reads from the buffer into the given element. Returns true if it was successfull, or false if the buffer was empty. */
            bool read(T& elem);
            /* Checks whether the buffer has any unread elements. */
            bool can_read();
    };
}

#endif