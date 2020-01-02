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
            Buffer(std::size_t size)
                :size(size)
            {
                // Create a buffer of the appropriate type and size
                this->buffer = new T[this->size];

                // Set the i's to zero.
                this->start_readable.store(0);
                this->start_writeable.store(0);
                this->is_empty.store(true);
            }
            ~Buffer() {
                delete[] this->buffer;
            }

            /* Writes given element to the buffer. Returns true if it was successfull, or false if the buffer was full. */
            bool write(T elem) {
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
            /* Checks whether the buffer has space for more elements. */
            bool can_write() const {
                // Only returns true if:
                //   - (start_writeable - start_readable) >= 0 && (end_readable - start_readable) <= size
                //   - (start_writeable - start_readable) < 0 && (end_readable + (size - start_readable)) <= size
                std::size_t start = this->start_readable.load();
                std::size_t end = this->start_writeable.load();
                bool empty = this->is_empty.load();
                return empty || start != end;
            }

            /* Reads from the buffer into the given element. Returns true if it was successfull, or false if the buffer was empty. */
            bool read(T& elem) {
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
            /* Checks whether the buffer has any unread elements. */
            bool can_read() const {
                // Only returns true if:
                //   - end_readable != start_readable
                std::size_t empty = this->is_empty.load();
                return !empty;
            }

            /* Used for debugging. Returns a three-line print which shows a 50-char long representation of the buffer, with two indicators where the start pos is (top) and the stop pos (bottom) */
            std::string to_string() const {
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
    };
}

#endif