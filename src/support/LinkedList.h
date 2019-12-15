/* LINKED LIST.h
*    by Lut99
*
*  Header file for LinkedList.cpp.
**/

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <string>
#include <cstddef>

namespace DataTypes {
    template <class T> struct Node {
        T value;
        Node<T> *next;
    };

    template <class T> class LinkedList {
        private:
            Node<T> *first;
            Node<T> *last;
            std::size_t size;

            /* Returns the node at the given position */
            Node<T> *get_node(std::size_t index);
        public:
            /* The LinkedList class can store any number of objects, of which the type is specified as object. Not very good at random access, though, but quick to rescale. */
            LinkedList();
            ~LinkedList();

            /* Returns the number of elements in the list */
            const std::size_t length() const;
            
            /* Prepends a new value to the beginning of the list */
            void prepend(T value);
            /* Inserts a new value at given location in the list */
            void insert(std::size_t index, T value);
            /* Appends a new value to the end of the list */
            void append(T value);

            /* Gets the value at the given index */
            T get(std::size_t index);

            /* Removes the value at given index from the list */
            void remove(std::size_t remove);

            /* Converts the list to a nice string representation */
            std::string to_string();

            /* Returns a pointer to a newly allocated array version of the LinkedList. Note that this will have to be deallocated later on. */
            T* to_array();
    };
}

#endif