#pragma once
#include <string>
#include "Node.h"

enum format {
  pre,
  in,
  post,
  tree
};

template <typename T>
class AVL {
  public: 
    void ins(T);
    void del(T);
    void print(); // default for print, calls print(in)
    void print(int);
    bool empty();

    AVL();
    AVL(T in);
    ~AVL();

  private:
    Node<T>* root; // top level root node
    int n; // item count
    
    void deleteNodes(Node<T>* node); // delete all nodes in tree from memory
    
    int calc_bf(Node<T>* node);
    int height(Node<T>* node);

    Node<T>* balance(Node<T>* node);

    Node<T>* ins_worker(Node<T>* n, T val);
    Node<T>* del_worker(Node<T>* n, T val);

    Node<T>* rot_L(Node<T>* node);
    Node<T>* rot_R(Node<T>* node);
    Node<T>* rot_LR(Node<T>* node);
    Node<T>* rot_RL(Node<T>* node);

    std::string prefix_str(Node<T>* node);
    std::string infix_str(Node<T>* node);
    std::string postfix_str(Node<T>* node);
    void print_tree(Node<T>* node, const std::string& prefix, bool isLeft); // see implementation reference
};

#include "AVL.tpp"