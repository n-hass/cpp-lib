#include <string>
#include <iostream>
#include "AVL.h"

template <typename T>
int AVL<T>::calc_bf(Node<T>* node) {
  node->bf = height(node->l) - height(node->r);
  return node->bf;
}

template <typename T>
int AVL<T>::height(Node<T>* node) {
  int h = 0;

  if (node != nullptr) {
    int x = height(node->l);
    int y = height(node->r);
    h = 1 + std::max(x,y);
  }

  return h;
}

template <typename T>
Node<T>* AVL<T>::balance(Node<T>* node) {
  Node<T>* newn = nullptr;

	// balance leaves of this node
	if( node->l )
		node->l = balance(node->l);
	if( node->r ) 
		node->r = balance(node->r);

	int bf = calc_bf(node);

  // now balance on this node
	if( bf > 1 ) { // left heavy test

		if( calc_bf( node->l ) < 0 ) // test if single or double rotation needed
			newn = rot_LR(node);
		else 
			newn = rot_L(node);

	} else if( bf < -1 ) { // right heavy test

		if( calc_bf( node->r ) > 0 ) // test if single or double rotation needed
			newn = rot_RL(node);
		else 
			newn = rot_R(node);

	} else { // node is already balanced
		newn = node;
	}

	return newn;
}
template <typename T>
void AVL<T>::ins(T in) {

  this->root = ins_worker(this->root,in); // must always save return to this->root incase top-level root has changed

}

template <typename T>
void AVL<T>::del(T in) {
  
  this->root = del_worker(this->root,in);
  
}

template <typename T>
Node<T>* AVL<T>::rot_L(Node<T>* node) {
  Node<T>* newn = node->l;
	node->l = newn->r;
	newn->r = node;

	return newn;
}

template <typename T>
Node<T>* AVL<T>::rot_R(Node<T>* node) {
  Node<T>* newn = node->r;
	node->r = newn->l;
	newn->l = node;

	return newn;
}

template <typename T>
Node<T>* AVL<T>::rot_LR(Node<T>* node) {
  Node<T>* tA = node->l;
  Node<T>* tB = tA->r;

  node->l = tB->r;
  tA->r = tB->l;
  tB->l = tA;
  tB->r = node;

  return tB;
}

template <typename T>
Node<T>* AVL<T>::rot_RL(Node<T>* node) {
  Node<T>* tA = node->r;
  Node<T>* tB = tA->l;

  node->r = tB->l;
  tA->l = tB->r;
  tB->r = tA;
  tB->l = node;

  return tB;
}

template <typename T>
Node<T>* AVL<T>::ins_worker(Node<T>* n, T val) {

  if (n == nullptr) {
    n = new Node<T>(val);
    return n;
  } 

  else if (val < n->data) {
    n->l = ins_worker(n->l, val);
    n = balance(n);
  } 
  else if (val > n->data) {
    n->r = ins_worker(n->r, val);
    n = balance(n);
  }

  return n;

}

template <typename T>
Node<T>* AVL<T>::del_worker(Node<T>* n, T val) {
  
  // element not found
	if (n == nullptr) 
    return nullptr;

  // continue traversal, element not found YET
	else if (val < n->data) 
    n->l = del_worker(n->l, val);

	else if (val > n->data) 
    n->r = del_worker(n->r, val);

  // delete, element found
	else {
    // node has both left and right leaves
    if ( (n->l!=nullptr) && (n->r!=nullptr) ) {
      Node<T>* t = n->l; // left subtree

      // find the largest node in the left subtree
      while(t->r != nullptr) 
        t = t->r;
      
      // replace the current node data to be deleted with a copy of the max of left subtree
      n->data = t->data;

      // remove the node that was copied (t)
      n->l = del_worker(n->l, t->data);
    }
    // node only has a right leaf
    else if(n->l == nullptr) {
      Node<T>* r = n->r;
      delete n;
      n = r;
    }
    // node has only a left leaf
    else if(n->r == nullptr) {
      Node<T>* l = n->l;
      delete n;
      n = l;
    }
  }

	if (n == nullptr)
    return n;

	n = balance(n);

  return n;
}

template <typename T>
bool AVL<T>::empty() {
  if (height(this->root) == 0)
    return true;
  else
    return false;
}

// PRINTING FUNCTIONS //
template <typename T>
void AVL<T>::print() { // default print(in)
  std::cout << infix_str("") << std::endl;
}

template <typename T>
void AVL<T>::print(int format) { // print with specified format
  std::string line = "";
  if (format == 0) 
    line = prefix_str(this->root);
  
  else if (format == 1) 
    line = infix_str(this->root);
  
  else if (format == 2) 
    line = postfix_str(this->root);
  
  else if (format == 3)
    print_tree(this->root, "", false);
  
  if (line != " " && line != "") {
    line = line.substr(0, line.size()-1); // remove last char (always a trailing space)
    std::cout << line << std::endl;
  }
}

template <typename T>
std::string AVL<T>::prefix_str(Node<T>* node) { // generate string to print
  std::string out;
  if (node == nullptr)
    return out;
  out += std::to_string(node->data) + " ";
  out += prefix_str(node->l);
  out += prefix_str(node->r);
  return out;
}

template <typename T>
std::string AVL<T>::infix_str(Node<T>* node) { // generate string to print
  std::string out;
  if (node == nullptr)
    return out;
  out += infix_str(node->l);
  out += std::to_string(node->data) + " ";
  out += infix_str(node->r);
  return out;
}

template <typename T>
std::string AVL<T>::postfix_str(Node<T>* node) { // generate string to print
  std::string out;
  if (node == nullptr)
    return out;
  out += postfix_str(node->l);
  out += postfix_str(node->r);
  out += std::to_string(node->data) + " ";
  return out;
}

/**
 * This printing function is not my own work and was used for debugging.
 * It is not part of the assessable code.
 * Function was adapted from https://stackoverflow.com/questions/36802354/print-binary-tree-in-a-pretty-way-using-c
 * 
 * In the original code, left is printed on top and right is on bottom. 
 *        I have flipped this because it made more sense to me :)
 */
template <typename T>
void AVL<T>::print_tree(Node<T>* node, const std::string& prefix, bool isRight) {

  if( node != nullptr ) {
    std::cout << prefix;

    std::cout << (isRight ? "├──" : "└──" );

    // print the value of the node
    std::cout << node->data << std::endl;

    // enter the next tree level - right then left branch for formatting
    print_tree( node->r, prefix + (isRight ? "│   " : "    "), true);
    print_tree( node->l, prefix + (isRight ? "│   " : "    "), false);
  }

}

// CONSTRUCTORS AND DESTRUCTORS //

template <typename T>
AVL<T>::AVL(T in) : AVL() { 
  this->root = new Node<T>(in);
}

template <typename T>
AVL<T>::AVL() { this->root = nullptr; n = 0; }

template <typename T>
void AVL<T>::deleteNodes(Node<T> * n) {

  if (n!=nullptr) {

    deleteNodes(n->l);
    deleteNodes(n->r);

    delete n;
  }
  
  return;
}

template <typename T>
AVL<T>::~AVL() { deleteNodes(this->root); }