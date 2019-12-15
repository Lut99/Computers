/* LINKED LIST.cpp
*    by Lut99
*
*  A datatstucture that mimics an array, except that it is very bad at random
*  access. The advantage is, however, that new elements can added without
*  much resizing, and that it can contain any type.
**/

#include <iostream>
#include <sstream>

#include "LinkedList.h"

using namespace std;
using namespace DataTypes;

template <class T> LinkedListIterator<T>::LinkedListIterator(LinkedList<T> l) {
    // Create a new element that's a copy of the given one
    this->l = l.copy();

    // Initialize the counters
    this->n = l->first;
}
template <class T> LinkedListIterator<T>::~LinkedListIterator() {
    delete this->l;
}
template <class T> bool LinkedListIterator<T>::next(T& value) {
    // Get the value
    value = this->n->value;
    this->n = this->n->next;
    return this->n != NULL;
}

/* CLASS DEFINITIONS */
template <class T> LinkedList<T>::LinkedList() {
    // Set the value
    this->first = NULL;
    this->last = NULL;
    this->size = 0;
}
template <class T> LinkedList<T>::~LinkedList() {
    // Undeclare any nodes
    Node<T> *temp;
    for (Node<T> *n = this->first; n != NULL;) {
        temp = n->next;
        delete n;
        n = temp;
    }
}

template <class T> Node<T>* LinkedList<T>::get_node(std::size_t index) {
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

template <class T> const std::size_t LinkedList<T>::length() const {
    return this->size;
}

template <class T> void LinkedList<T>::prepend(T value) {
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
template <class T> void LinkedList<T>::insert(std::size_t index, T value) {
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
template <class T> void LinkedList<T>::append(T value) {
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

template <class T> T LinkedList<T>::get(std::size_t index) {
    // Get the node at that index
    Node<T> *n = this->get_node(index);
    // Return the value
    return n->value;
}

template <class T> void LinkedList<T>::remove(std::size_t index) {
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

template <class T> std::string LinkedList<T>::to_string() {
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

template <class T> T* LinkedList<T>::to_array() {
    T* to_return = new T[this->size];
    std::size_t i = 0;
    for (Node<T> *n = this->first; n != NULL; n = n->next) {
        to_return[i] = n->value;
        i++;
    }
    return to_return;
}

template <class T> LinkedList<T>* LinkedList<T>::copy() {
    // Create the new object
    LinkedList<T> *to_return = new LinkedList<T>;
    // For every item, append that value to the other side
    for (Node<T> *n = this->first; n != NULL; n = n->next) {
        to_return->append(n);
    }
    // Done
    return to_return;
}