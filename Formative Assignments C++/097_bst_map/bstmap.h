#pragma once
#include <stddef.h>

#include <iostream>
#include <stdexcept>

#include "map.h"

template<typename K, typename V>
class BstMap : public Map<K, V> {
  class Node {
   public:
    Node * left;
    Node * right;
    K key;
    V value;
    Node(const K & k, const V & v) : left(NULL), right(NULL), key(k), value(v) {}
    Node(Node * l, Node * r, const K & k, const V & v) :
        left(l),
        right(r),
        key(k),
        value(v) {}
  };

 public:
  Node * root;

 public:
  BstMap() : root(NULL) {}
  BstMap(const BstMap & b) : root(NULL) {
    //write copy constructor
    addAllBelow(b.root);
  }

  void addAllBelow(Node * current) {
    if (current != NULL) {
      add(current->key, current->value);
      addAllBelow(current->left);
      addAllBelow(current->right);
    }
  }

  BstMap & operator=(const BstMap & b) {
    //write operator =
    if (this != &b) {
      BstMap * temp = new BstMap;
      temp->addAllBelow(b.root);
      destroy(root);
      root = temp->root;
      temp->root = NULL;
      delete temp;
    }
    return *this;
  }
  virtual ~BstMap() {
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

  virtual void add(const K & key, const V & value) {
    /*if (root == NULL) {
      root = new Node(key, value);
    }
    else {
      if (key < root->key) {
        BstMap leftBranch;
        leftBranch.root = root->left;
        leftBranch.add(key, value);
        root->left = leftBranch.root;
        leftBranch.root = NULL;
      }
      if (key > root->key) {
        BstMap rightBranch;
        rightBranch.root = root->right;
        rightBranch.add(key, value);
        root->right = rightBranch.root;
        rightBranch.root = NULL;
      }
      else {
        root->value = value;
      }
      }*/
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
        (*curr)->value = value;
      }
    }
    *curr = new Node(key, value);
  }

  virtual void remove(const K & key) {
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
          (*curr)->value = (*child_curr)->value;
          Node * temp = (*child_curr)->left;
          (*child_curr)->left = NULL;
          delete *child_curr;
          *child_curr = temp;
          return;
        }
      }
    }
  }

  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
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
        return curr->value;
      }
    }
    throw std::invalid_argument("no element found with the given key");
  }
};
