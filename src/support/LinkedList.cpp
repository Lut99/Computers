/* LINKED LIST.cpp
*    by Lut99
*
*  A datatstucture that mimics an array, except that it is very bad at random
*  access. The advantage is, however, that new elements can added without
*  much resizing, and that it can contain any type.
**/

#include <sstream>

#include "LinkedList.h"

using namespace std;
using namespace DataTypes;

/* VALUE TO STRING CONVERSION */
template <typename T> const std::string value_to_string(T value) {
    // Three cases:
    if (std::is_integral<T>::value) {
        // Return the to_string value of it
        return std::to_string(value);
    } else if (std::is_pointer<T>::value) {
        // Return the to_string value of it, after casted to int
        return std::to_string(reinterpret_cast<std::uintptr_t>(value));
    }
    // Else, return constant value
    return "<element>";
}
template <> const std::string value_to_string(std::string value) {
    // Simply return the value, but wrapped in ""
    return "\"" + value + "\"";
}
template <> const std::string value_to_string(char *value) {
    // Simply return the value as string, but wrapped in ""
    std::string s_value(value);
    return "\"" + s_value + "\"";
}

/* CLASS DEFINITIONS */
template <typename T> LinkedList<T>::LinkedList() {
    // Set the first pointer to NULL
    this->first_node = NULL;
    // Set the size to 0
    this->n_nodes = 0;
}
template <typename T> LinkedList<T>::~LinkedList() {
    // Undeclare any nodes recursively
    for (Node<T> *next = this->first_node; next != NULL;) {
        Node<T> *temp = next->next;
        delete next;
        next = temp;
    }
}

template <typename T> void LinkedList<T>::insert(std::size_t index, T value) {
    // Check if the index is valid
    if (index < 0 || index > this->n_nodes) {
        throw runtime_error("Index too large; " + std::to_string(index) + " > " + std::to_string(this->n_nodes));
    }

    // Create new node
    Node<T> *new_node = new Node<T>;
    new_node->value = value;
    new_node->next = NULL;

    // Get the node at the correct position
    Node<T> *prv_node = NULL;
    Node<T> *old_node = this->first_node;
    for (int i = 0; i < index; i++) {
        // Advance to the next node
        prv_node = old_node;
        old_node = old_node->next;
    }
    if (old_node == NULL) {
        // No need to replace, just add to the end
        prv_node->next = new_node;
    } else {
        // Put the new_node in between these two
        prv_node->next = new_node;
        new_node->next = old_node;
    }
    this->n_nodes++;

    // Done
}
template <typename T> void LinkedList<T>::append(T value) {
    // Return the insert at position (end)
    return this->insert(this->n_nodes, value);
}
template <typename T> void LinkedList<T>::prepend(T value) {
    // Return the insert at position 0
    return this->insert(0, value);
}

template <typename T> T LinkedList<T>::get(std::size_t index) {
    // Check if the index is valid
    if (index < 0 || index >= this->n_nodes) {
        throw runtime_error("Index too large; " + std::to_string(index) + " >= " + std::to_string(this->n_nodes));
    }

    // Iterate until the correct index has been reached
    Node<T> node = this->first_node;
    for (int i = 0; i <= index; i++) {
        node = node->next;
    }

    // Return that value
    return node->value;
}
template <typename T> T LinkedList<T>::operator[](std::size_t index) {
    // Return the get-equivalent
    return this->get(index);
}

template <typename T> void LinkedList<T>::remove(std::size_t index) {
    // Check if the index is valid
    if (index < 0 || index >= this->n_nodes) {
        throw runtime_error("Index too large; " + std::to_string(index) + " >= " + std::to_string(this->n_nodes));
    }

    // Get the node at the correct position
    Node<T> *prv_node = NULL;
    Node<T> *rem_node = this->first_node;
    for (int i = 0; i < index; i++) {
        // Advance to the next node
        prv_node = rem_node;
        rem_node = rem_node->next;
    }

    // Set the pointers correctly
    prv_node->next = rem_node->next;

    // Remove the rem_node
    delete rem_node;
}

template <typename T> const std::size_t LinkedList<T>::length() const {
    return this->n_nodes;
}

template <typename T> const std::string LinkedList<T>::to_string() const {
    stringstream sstr;
    sstr << "[";
    for (Node<T> *node = this->first_node; node != NULL; node = node->next) {
        if (node != this->first_node) {
            sstr << ", ";
        }
        sstr << this->value_to_string(node->value);
    }
    sstr << "]";
    return sstr.str();
}