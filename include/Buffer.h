/* BUFFER.h
*    by Lut99
*
*  Header file for Buffer.cpp.
**/

#ifndef BUFFER_H
#define BUFFER_H

#include <atomic>
#include <cstddef>

namespace DataTypes {
    template <class T> class Buffer {
        private:
            T *buffer;

            std::atomic<std::size_t> start_readable;
            //std::size_t start_readable;
            std::atomic<std::size_t> start_writeable;
            //std::size_t end_readable;
            std::atomic<bool> is_empty;
        public:
            const std::size_t size;

            /* The buffer class provides a thread-safe way for one thread to push a continious stream of information to a second thread. Uses no locks whatsoever. */
            Buffer(std::size_t size);
            ~Buffer();

            /* Writes given element to the buffer. Returns true if it was successfull, or false if the buffer was full. */
            bool write(T elem);
            /* Checks whether the buffer has space for more elements. */
            bool can_write() const;

            /* Reads from the buffer into the given element. Returns true if it was successfull, or false if the buffer was empty. */
            bool read(T& elem);
            /* Checks whether the buffer has any unread elements. */
            bool can_read() const;

            /* Used for debugging. Returns a three-line print which shows a 50-char long representation of the buffer, with two indicators where the start pos is (top) and the stop pos (bottom) */
            std::string to_string() const;
    };
}

#endif