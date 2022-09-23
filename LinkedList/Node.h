#ifndef LL_NODE_H
#define LL_NODE_H

template <typename T>
class Node {
    template<typename U>
    friend class LinkedList;
private:
    T data;
    Node* previous;
    Node* next;

    // update state
    void set_previous(Node*);
    void set_next(Node*);

public:
    Node();
    Node(T);
    ~Node();

    void set_data(T);
    T get_data();
    Node* get_next();
    Node* get_previous();
};
#include "Node.tpp"
#endif