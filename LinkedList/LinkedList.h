#ifndef MY_LINKEDLIST_H
#define MY_LINKEDLIST_H
#include "Node.h"

template <typename T>
class LinkedList {
private:
    // state
    Node<T>* head;
    Node<T>* tail;

    // helpers
    Node<T>* traverse(int pos);

public:
    // interface methods
    void addFront(T newItem);
    void addEnd(T newItem);
    void addAtPosition(int pos, T newItem);

    int search(T item); // return index of item

    void deleteFront();
    void deleteEnd();
    void deletePosition(int pos);
    void replace(int pos, T newItem);

    T getItem(int pos); // return item at position specified (base 1)
    void printItems();
    void printReverse();


    // operators
    T operator[](int index); // return item at index (base 0)

    // destructors and constructors
    LinkedList();
    LinkedList(T* A, int n); // constructs linkedlist with elements from array
    ~LinkedList();
};
#include "LinkedList.tpp"
#endif