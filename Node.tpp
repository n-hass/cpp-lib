#include "Node.h"

template <typename T>
T Node<T>::get_data(){
    return data;
}

template <typename T>
void Node<T>::set_data(T data){
    this->data = data;
}

template <typename T>
Node<T>* Node<T>::get_next(){
    return next;
}

template <typename T>
void Node<T>::set_next(Node* next){
    this->next = next;
}

template <typename T>
Node<T>* Node<T>::get_previous(){
    return previous;
}

template <typename T>
void Node<T>::set_previous(Node<T>* previous){
    this->previous = previous;
}

// de/constructors
template <typename T>
Node<T>::Node(){
    next = nullptr;
    previous = nullptr;
}

template <typename T>
Node<T>::Node(T data) {
    this->data = data;
    next = nullptr;
    previous = nullptr;
}

template <typename T>
Node<T>::~Node(){}