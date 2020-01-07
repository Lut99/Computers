/* ARRAY.h
*    by Lut99
*
*  A file that allows the user to create a simple array that is modifieable
*  after creation. Note that, unlike LinkedList.h, this has a terrible resize
*  complexity but very fast access complexity.
**/

#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <cstddef>
#include <stdexcept>
#include <limits.h>

namespace DataTypes {
    template <class T> class Array {
        private:
            T* data;
            std::size_t size;
        
        public:
            /* The array class provides a python-like array that can resize (though with terrible complexity) and holds information about it's own size. By default, it initializes with a size of 0 and has to be appended. */
            Array(std::size_t size = 0) {
                // Initialize the inner array
                this->data = new T[size];
                this->size = size;
            }
            /* The array class provides a python-like array that can resize (though with terrible complexity) and holds information about it's own size. This overload initializes it with data and size from given, normal array. */
            Array(T* data, std::size_t n) {
                // Initialize the inner array
                this->data = new T[n];
                this->size = n;

                // Copy all elements
                for (std::size_t i = 0; i < n; i++) {
                    this->data[i] = data[i];
                }
            }
            /* The array class provides a python-like array that can resize (though with terrible complexity) and holds information about it's own size. This overload initializes it with data and size from given Array object. */
            Array(Array<T>& arr) {
                // Initialize the inner array
                this->size = arr.length();
                this->data = new T[this->size];
                
                // Copy the elements
                for (std::size_t i = 0; i < this->size; i++) {
                    this->data[i] = arr[i];
                }
            }
            ~Array() {
                delete[] this->data;
            }

            /* Returns the length of an element in the array */
            const std::size_t length() const {
                return this->size;
            }

            /* Adds an element at the end of the array. Note that this resizes the array, and that this is done with a very high complexity. */
            Array<T>& append(T elem) {
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

                // Return the array for chainability
                return *this;
            }

            /* Resets the array to a size of 0 */
            Array<T>& clear() {
                // Create new data
                T* new_data = new T[0];
                std::size_t new_size = 0;

                // Deallocate old
                delete[] this->data;

                // Overwrite
                this->data = new_data;
                this->size = new_size;
            }

            /* Returns a copy of the inner array at the given pointer location. */
            void c_arr(T* result) {
                for (std::size_t i = 0; i < this->size; i++) {
                    result[i] = this->data[i];
                }
            }

            /* Returns a subset of the current array as new array (copies elements). The result array is always cleared, even if anything is out of bounds, and is also returned so that easy chainability can be obtained. */
            Array<T>& subset(Array<T>& result, std::size_t pos, std::size_t length = ULONG_MAX) {
                // Clear the array
                result.clear();
                // Do nothing if the subset is out-of-bounds
                if (pos < 0 || pos >= this->size) {
                    return result;
                }
                // First, compute the actual length
                std::size_t act_length = this->size - pos;
                // If the length is shorter, use that instead
                if (length < act_length) {
                    act_length = length;
                }

                // Resize the array to have that many elements
                result.resize(act_length);

                // Copy the appropriate elements over
                for (std::size_t i = 0; i < act_length; i++) {
                    result[i] = this->data[pos + i];
                }

                // Done, return
                return result;
            }

            /* Resizes the array to a new size. Note that, if the new size is smaller than the old, any overflow elements will be discarded (without clearing them in any way). This array is returned for chainability. */
            Array<T>& resize(std::size_t new_size) {
                // Allocate new space
                T* new_data = new T[new_size];

                // Loop and copy until either bound has been reached
                for (std::size_t i = 0; i < this->size && i < new_size; i++) {
                    new_data[i] = this->data[i];
                }

                // Deallocate the old one
                delete[] this->data;

                // Overwrite existing pointers and stuff
                this->data = new_data;
                this->size = new_size;

                // Done
                return *this;
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