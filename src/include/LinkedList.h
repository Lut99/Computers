/* LINKED LIST.h
*    by Lut99
*
*  Header file for LinkedList.cpp.
**/

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <string>
#include <cstddef>

#include "Array.h"

namespace DataTypes {
    template <class T> struct Node {
        T value;
        Node<T> *next;
    };

    template <class T> class LinkedListIterator;

    template <class T> class LinkedList {
        private:
            Node<T> *first;
            Node<T> *last;
            std::size_t size;

            /* Returns the node at the given position */
            Node<T> *get_node(std::size_t index) {
                // Check if the index is out of bounds
                if (index < 0 || index >= this->size) {
                    // Error: out-of-bounds
                    throw runtime_error("Index out of bounds: " + std::to_string(index) + " >= " + std::to_string(this->size));
                }
                // Loop until found
                Node<T> *to_return = this->first;
                for (std::size_t i = 0; i < index; i++) {
                    to_return = to_return->next;
                }
                return to_return;
            }
        public:
            /* The LinkedList class can store any number of objects, of which the type is specified as object. Not very good at random access, though, but quick to rescale. */
            LinkedList() {
                // Set the value
                this->first = NULL;
                this->last = NULL;
                this->size = 0;
            }
            /* Copy constructor */
            LinkedList(LinkedList<T>& list) {
                // Create new nodes, in chain
                Node<T> *n = NULL;
                Node<T> *prev_n = NULL;
                this->size = 0;
                for (Node<T> *list_n = list.first; list_n != NULL; list_n = list_n->next) {
                    n = new Node<T>;
                    n->value = list_n->value;
                    n->next = NULL;

                    if (list_n == list.first) {
                        // Set it as first
                        this->first = n;
                    } else {
                        prev_n->next = n;
                    }
                    prev_n = n;
                    this->size++;
                }
                // Set the last pointer correct
                this->last = n;

            }
            /* Additional copy constructor for the LinkedList. */
            ~LinkedList() {
                // Undeclare any nodes
                Node<T> *temp;
                for (Node<T> *n = this->first; n != NULL;) {
                    temp = n->next;
                    delete n;
                    n = temp;
                }
            }

            /* Returns the number of elements in the list */
            const std::size_t length() const {
                return this->size;
            }
            
            /* Prepends a new value to the beginning of the list */
            void prepend(T value) {
                Node<T> *new_node = new Node<T>;
                new_node->value = value;

                // Put it at the start
                new_node->next = this->first;
                this->first = new_node;

                // Increment the size
                this->size++;

                // Update the last pointer (if applicable)
                if (new_node->next == NULL) {
                    this->last = new_node;
                }
            }
            /* Inserts a new value at given location in the list */
            void insert(std::size_t index, T value) {
                // Undertake particular action if needed
                if (index == 0) {
                    // Run prepend instead
                    return this->prepend(value);
                } else if (index == this->size) {
                    // Run append
                    return this->append(value);
                } else if (index < 0 || index > this->size) {
                    // Error: out-of-bounds
                    throw runtime_error("Index out of bounds: " + std::to_string(index) + " > " + std::to_string(this->size));
                }

                Node<T> *new_node = new Node<T>;
                new_node->value = value;

                // Now index is within bounds and not an edge, get the node before the index
                Node<T> *prev_node = this->get_node(index - 1);

                // Now insert new_node between prev_node and it's next one
                new_node->next = prev_node->next;
                prev_node->next = new_node;

                // Increment the size
                this->size++;

                // Update the last pointer (if applicable)
                if (new_node->next == NULL) {
                    this->last = new_node;
                }
            }
            /* Appends a new value to the end of the list */
            void append(T value) {
                Node<T> *new_node = new Node<T>;
                new_node->value = value;

                // Put it at the end
                if (this->last != NULL) {
                    this->last->next = new_node;
                }
                this->last = new_node;
                new_node->next = NULL;

                // Update first as well
                if (this->first == NULL) {
                    this->first = new_node;
                }

                // Increment the size
                this->size++;
            }

            /* Gets the value at the given index */
            T get(std::size_t index) {
                // Get the node at that index
                Node<T> *n = this->get_node(index);
                // Return the value
                return n->value;
            }

            /* Removes the value at given index from the list */
            void remove(std::size_t remove) {
                // Check if witin bounds
                if (index < 0 || index >= this->size) {
                    throw runtime_error("Index out of bounds: " + std::to_string(index) + " >= " + std::to_string(this->size));
                }
                
                // If the first index, undertake special action
                if (index == 0) {
                    Node<T> *to_remove = this->first;
                    this->first = to_remove->next;
                    delete to_remove;
                    return;
                }

                // Otherwise, loop to find the node preceding this one
                Node<T> *prev_node = this->get_node(index - 1);
                Node<T> *to_remove = prev_node->next;

                // Set the pointers correctly
                prev_node->next = to_remove->next;
                delete to_remove;

                // Update the size
                this->size--;

                // Update the last if needed
                if (prev_node->next == NULL) {
                    this->last = prev_node;
                }
            }

            /* Converts the list to a nice string representation */
            std::string to_string() {
                std::stringstream sstr;
                sstr << "[";
                // Loop through the elements and print them all out
                for (Node<T> *n = this->first; n != NULL; n = n->next) {
                    // Determine if a comma is to be added
                    if (n != this->first) {
                        sstr << ", ";
                    }
                    sstr << n->value;

                    // Quit the loop
                    if (n->next != NULL && n == n->next->next) {
                        std::cout << n->value << std::endl;
                        std::cout << n->next->value << std::endl;
                        break;
                    }
                }
                // Add final ] and return
                sstr << "]";
                return sstr.str();
            }

            /* Returns all values stored in this LinkedList as DataTypes Array object. Note that it must have the same type as this LinkedList to work. */
            void to_array(Array<T>& to_return) {
                std::size_t i = 0;
                for (Node<T> *n = this->first; n != NULL; n = n->next) {
                    to_return[i] = n->value;
                    i++;
                }

                return to_return;
            }

            /* Returns a pointer to a newly allocated c-style array version of the LinkedList. Note that this will have to be deallocated later on. */
            T* c_arr() {
                T* to_return = new T[this->size];
                std::size_t i = 0;
                for (Node<T> *n = this->first; n != NULL; n = n->next) {
                    to_return[i] = n->value;
                    i++;
                }
                return to_return;
            }

            /* Lets the iterator be a friend for efficient memory access. */
            friend class LinkedListIterator<T>;
    };

    template <class T> class LinkedListIterator {
        private:
            LinkedList<T> *l;
            Node<T> *n;
            int i;
            int max;
        public:
            /* The LinkedListIterator is used to get the elements stored in the LinkedList one-by-one. Note that the LinkedList in question is copied, and can therefore be modified during iteration. */
            LinkedListIterator(LinkedList<T> l) {
                // Create a new element that's a copy of the given one
                this->l = new LinkedList<T>(l);

                // Initialize the counters
                this->n = this->l->first;
                this->i = 0;
                this->max = this->l->length();
            }
            ~LinkedListIterator() {
                delete this->l;
            }

            /* Get the next element of the LinkedList. */
            bool next(T& elem) {
                // Get the value
                if (this->n != NULL) {
                    value = this->n->value;
                    this->n = this->n->next;
                }
                i++;
                return this->i <= this->max;
            }
    };
}

#endif