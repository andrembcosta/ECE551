#ifndef _LL_H_
#define _LL_H_
#include <assert.h>

#include <cstdlib>
#include <exception>
#include <iostream>

//YOUR CODE GOES HERE
void testList(void);

class OutOfBounds : public std::exception {
 public:
  virtual const char * what() const throw() {
    return "index requested is out of bounds\n";
  }
};

template<typename T>
class LinkedList {
 private:
  class Node {
   public:
    T data;
    Node * next;
    Node * prev;
    Node(const T & d) : data(d), next(NULL), prev(NULL){};
    Node(const T & d, Node * p, Node * n) : data(d), next(n), prev(p){};
  };
  Node * head;
  Node * tail;
  int size;

 public:
  LinkedList() : head(NULL), tail(NULL), size(0) {}

  LinkedList(const LinkedList & rhs) : head(NULL), tail(NULL), size(0) {
    for (int i = 0; i < rhs.size; i++) {
      addBack(rhs[i]);
    }
  }

  LinkedList & operator=(const LinkedList & rhs) {
    if (this != &rhs) {
      LinkedList<T> * temp = new LinkedList(rhs);
      while (head != NULL) {
        Node * temp2 = head->next;
        delete head;
        head = temp2;
      }
      head = temp->head;
      tail = temp->tail;
      size = rhs.size;
      temp->head = NULL;
      temp->tail = NULL;
      delete temp;
    }
    return *this;
  }

  ~LinkedList() {
    while (head != NULL) {
      Node * temp = head->next;
      delete head;
      head = temp;
    }
  }
  void addFront(const T & item) {
    if (head == NULL) {
      head = new Node(item, NULL, NULL);
      tail = head;
    }
    else {
      head = new Node(item, NULL, head);
      head->next->prev = head;
    }
    size++;
  }
  void addBack(const T & item) {
    if (head == NULL) {
      tail = new Node(item, NULL, NULL);
      head = tail;
    }
    else {
      tail = new Node(item, tail, NULL);
      tail->prev->next = tail;
    }
    size++;
  }
  bool remove(const T & item) {
    Node ** curr = &head;
    int counter = 0;
    while (counter < size) {
      if ((*curr)->data == item) {
        break;
      }
      curr = &(*curr)->next;
      counter++;
    }
    if (counter == size) {
      return false;
    }
    if (counter == size - 1) {
      tail = (*curr)->prev;
    }
    else {
      (*curr)->next->prev = (*curr)->prev;
    }
    Node * temp = *curr;
    *curr = (*curr)->next;
    delete temp;
    size--;
    return true;
  }

  T & operator[](int index) {
    if (index < 0 || index > size - 1) {
      throw OutOfBounds();
    }
    Node ** curr = &head;
    for (int i = 0; i < index; i++) {
      curr = &(*curr)->next;
    }
    return (*curr)->data;
  }

  const T & operator[](int index) const {
    if (index < 0 || index > size - 1) {
      throw OutOfBounds();
    }
    Node * const * curr = &head;
    for (int i = 0; i < index; i++) {
      curr = &(*curr)->next;
    }
    return (*curr)->data;
  }

  int find(const T & item) {
    Node ** curr = &head;
    int counter = 0;
    while (counter < size) {
      if ((*curr)->data == item) {
        return counter;
      }
      curr = &(*curr)->next;
      counter++;
    }
    return -1;
  }

  int getSize() const { return size; }
  friend void testList(void);
};

#endif
