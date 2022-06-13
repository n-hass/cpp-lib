#include "LinkedList.h"
#include "Node.h"
#include <iostream>
#include <limits>
#include <exception>

template <typename T>
Node<T>* LinkedList<T>::traverse(int pos){
    if (pos < 1)
        return nullptr;

    Node<T>* e = head;
    int i=1;
    while (e != nullptr && i<pos){
        e = e->get_next();
        i++;
    }

    return e;
}

template <typename T>
void LinkedList<T>::addFront(T newItem){
    Node<T>* newNext = head;
    head = new Node<T>(newItem);

    if (newNext != nullptr){
        head->set_next(newNext);
        newNext->set_previous(head);

        //while(tail->get_next() != nullptr) 
            //tail = tail->get_next();
    } else {
        tail = head;
    }
}

template <typename T>
void LinkedList<T>::addEnd(T newItem) {
    if (tail == nullptr){
        addFront(newItem);
    } else {
        tail->set_next(new Node<T>(newItem));
        tail->get_next()->set_previous(tail);
        tail = tail->get_next();
    }
}

template <typename T>
void LinkedList<T>::addAtPosition(int pos, T newItem){
    // get the element in the position before the new element
    Node<T>* e = traverse(pos-1); // this is the base
    
    if (e == nullptr) this->addEnd(newItem);
    else {
        Node<T>* newEle = new Node<T>(newItem); // create new node
        newEle->set_next(e->get_next()); // set the next pointer of the new node to the next of the base
        newEle->set_previous(e); // set the previous pointer of the new node to the base

        e->get_next()->set_previous(newEle); // set the new node as the previous to the original base+1 node
        e->set_next(newEle); // set the next pointer of the base to the new element
    }
}

template <typename T>
int LinkedList<T>::search(T item){
    Node<T>* e = head;
    int i = 1;
    while (e!=nullptr){
        if (e->get_data() == item) break;
        else e = e->get_next();
        i++;
    }
    if (e==nullptr){
        //std::cout << 0 << " ";// << std::endl;
        throw std::runtime_error("Not found in list");
    } else {
        //std::cout << i << " ";// << std::endl;
        return i;
    }
}

template <typename T>
void LinkedList<T>::deleteFront(){
    Node<T>* old = head;
    head = head->get_next();
    head->set_previous(nullptr);
    delete old;
}

template <typename T>
void LinkedList<T>::deleteEnd(){
    Node<T>* old = tail;
    tail = tail->get_previous();
    tail->set_next(nullptr);
    delete old;
}

template <typename T>
void LinkedList<T>::deletePosition(int pos){
    Node<T>* e = traverse(pos-1); // get element previous to the position being deleted
    if (e == nullptr){ 
        throw std::range_error("Outside range");
    }
    Node<T>* old = e->get_next();
    e->set_next( old->get_next() );
    e->get_next()->set_previous(e);
    delete old;
}

template <typename T>
void LinkedList<T>::replace(int pos, T newItem){
    Node<T>* e = traverse(pos);
    if (e == nullptr){
        throw std::range_error("Outside range");
    }
    e->set_data(newItem);
}

template <typename T>
T LinkedList<T>::getItem(int pos){
    Node<T>* e = traverse(pos);

    if (e == nullptr){
        throw std::range_error("Outside range");
    }

    //std::cout << e->get_data() << " ";// << std::endl;
    return e->get_data();
}

template <typename T>
void LinkedList<T>::printItems(){
    Node<T>* e = head;
    if (e!=nullptr){
        std::cout << e->get_data();
        e = e->get_next();
        while (e!=nullptr){
            std::cout << " " << e->get_data();
            e = e->get_next();
        }
        std::cout << std::endl;
    }
}

template <typename T>
void LinkedList<T>::printReverse(){
    Node<T>* e = tail;
    if (e!=nullptr){
        std::cout << e->get_data();
        e = e->get_previous();
        while (e!=nullptr){
            std::cout << " " << e->get_data();
            e = e->get_previous();
        }
        std::cout << std::endl;
    }
}

/**
 * index starts at 0. translation to position: pos = index+1
 */
template <typename T>
T LinkedList<T>::operator[](int index){
    return this->search(index+1);
}

// de/constructors
template <typename T>
LinkedList<T>::LinkedList(){
    head = nullptr;
    tail = nullptr;
}

template <typename T>
LinkedList<T>::LinkedList(T*A, int n){
    head = new Node<T>(A[0]);
    tail = head;
    for (int i=1; i<n; i++){
        this->addEnd(A[i]);
    }
}

template <typename T>
LinkedList<T>::~LinkedList() {
    Node<T>* element = head;
    Node<T>* newHead = nullptr;
    while(element != nullptr){
        // delete node
        newHead = element->get_next();
        delete element;
        element = newHead;
    }
}