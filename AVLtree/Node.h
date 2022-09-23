#pragma once
#include <iostream>

template <typename T>
struct Node {
    
    T data;
    Node* l; // left node
    Node* r; // right node
    
    int bf; // balance factor = height(left subtree) - height(right subtree)

    Node() { l = nullptr; r = nullptr; }
    Node(T in) : Node() { data = in; }
    ~Node() {}

};