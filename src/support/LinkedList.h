/* LINKED LIST.h
*    by Lut99
*
*  Header file for LinkedList.cpp.
**/

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <cstddef>
#include <string>

namespace DataTypes {
    template <typename T> struct Node {
        T value;
        Node<T> *next;
    };
    
    template <typename T> class LinkedList {
        private:
            Node<T> *first_node;
            std::size_t n_nodes;
        public:
            /* The LinkedList class can store any number of objects, of which the type is specified as object. Not very good at random access, though, but quick to rescale. */
            LinkedList();
            ~LinkedList();

            /* Inserts a new value into the list at position index. If another value was there before, it and all other values are pushed forward. */
            void insert(std::size_t index, T value);
            /* Appends a new value to the end of the list. */
            void append(T value);
            /* Prepends a new value to the beginning of the list. All other values are pushed back. */
            void prepend(T value);

            /* Returns the value at position index. */
            T get(std::size_t index);
            /* Gets the value at the given index, but then as array subscript. */
            T operator[](std::size_t index);

            /* Removes the value at the given index. */
            void remove(std::size_t index);

            /* Returns the number of elements currently stored */
            const std::size_t length() const;

            /* Returns a string representation of the linkedlist. Only for some element types their value is shown. Otherwise, it just says "<element_i>". */
            const std::string to_string() const;
    };
}

#endif