#pragma once
#include <stddef.h>

#include <iostream>
#include <stdexcept>

#include "set.h"

template<typename T>
class BstSet : public Set<T> {
  class Node {
   public:
    Node * left;
    Node * right;
    T key;
    Node(const T & k) : left(NULL), right(NULL), key(k) {}
    Node(Node * l, Node * r, const T & k) : left(l), right(r), key(k) {}
  };

 public:
  Node * root;

 public:
  BstSet() : root(NULL) {}
  BstSet(const BstSet & b) : root(NULL) {
    //write copy constructor
    addAllBelow(b.root);
  }

  void addAllBelow(Node * current) {
    if (current != NULL) {
      add(current->key);
      addAllBelow(current->left);
      addAllBelow(current->right);
    }
  }

  BstSet & operator=(const BstSet & b) {
    //write operator =
    if (this != &b) {
      BstSet * temp = new BstSet;
      temp->addAllBelow(b.root);
      destroy(root);
      root = temp->root;
      temp->root = NULL;
      delete temp;
    }
    return *this;
  }
  virtual ~BstSet() {
    //write destructor
    destroy(root);
  }

  void destroy(Node * current) {
    if (current != NULL) {
      destroy(current->left);
      Node * temp = current->right;
      delete current;
      current = temp;
      destroy(current);
    }
  }

  virtual void add(const T & key) {
    Node ** curr = &root;
    while (*curr != NULL) {
      if (key < (*curr)->key) {
        curr = &((*curr)->left);
        continue;
      }
      if (key > (*curr)->key) {
        curr = &((*curr)->right);
        continue;
      }
    }
    *curr = new Node(key);
  }

  virtual void remove(const T & key) {
    Node ** curr = &root;
    while (*curr != NULL) {
      if (key < (*curr)->key) {
        curr = &((*curr)->left);
        continue;
      }
      if (key > (*curr)->key) {
        curr = &((*curr)->right);
        continue;
      }
      else {
        if ((*curr)->left == NULL) {
          Node * temp = (*curr)->right;
          (*curr)->right = NULL;
          delete *curr;
          *curr = temp;
          return;
        }
        if ((*curr)->right == NULL) {
          Node * temp = (*curr)->left;
          (*curr)->left = NULL;
          delete *curr;
          *curr = temp;
          return;
        }
        else {
          Node ** child_curr = curr;
          child_curr = &((*child_curr)->left);
          while ((*child_curr)->right != NULL) {
            child_curr = &((*child_curr)->right);
          }
          (*curr)->key = (*child_curr)->key;
          Node * temp = (*child_curr)->left;
          (*child_curr)->left = NULL;
          delete *child_curr;
          *child_curr = temp;
          return;
        }
      }
    }
  }

  virtual bool contains(const T & key) const {
    Node * curr = root;
    while (curr != NULL) {
      if (key < curr->key) {
        curr = curr->left;
        continue;
      }
      if (key > curr->key) {
        curr = curr->right;
        continue;
      }
      else {
        return true;
      }
    }
    return false;
  }
};
