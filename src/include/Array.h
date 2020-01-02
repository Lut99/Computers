/* ARRAY.h
*    by Lut99
*
*  A file that allows the user to create a simple array that is modifieable
*  after creation. Note that, unlike LinkedList.h, this has a terrible resize
*  complexity but very fast access complexity.
**/

#ifndef ARRAY_H
#define ARRAY_H

#include <cstddef>
#include <stdexcept>

namespace DataTypes {
    template <class T> class Array {
        private:
            T* data;
            std::size_t size;
        
        public:
            /* The array class provides a python-like array that can resize (though with terrible complexity) and holds information about it's own size. */
            Array(std::size_t size = 0) {
                // Initialize the inner array
                this->data = new T[size];
                this->size = size;
            }
            ~Array() {
                delete[] this->data;
            }

            /* Returns the length of an element in the array */
            const std::size_t length() const {
                return this->size;
            }

            /* Adds an element at the end of the array. Note that this resizes the array, and that this is done with a very high complexity. */
            void append(T elem) {
                // First, resize the array to +1
                std::size_t new_size = this->size + 1;
                T *new_data = new T[new_size];

                // Copy the elements
                for (std::size_t i = 0; i < this->size; i++) {
                    new_data[i] = this->data[i];
                }
                // Deallocate the old array
                delete[] this->data;
                // Overwrite values
                this->size = new_size;
                this->data = new_data;

                // Now put the element in the last position
                this->operator[](this->size - 1) = elem;
            }

            /* Returns a reference to a value in the array. Throws an out_of_range exception if the index is out of range. */
            T& operator[](std::size_t index) {
                // Check if the index is within bounds
                if (index < 0 || index >= this->size) {
                    throw std::out_of_range("index " + std::to_string(index) + " is out of range (size: " + std::to_string(this->size) + ")");
                }

                // Return the object pointed at
                return this->data[index];
            }
    };
}

#endif