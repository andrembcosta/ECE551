#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "il.h"

void testList() {
  IntList a = IntList();
  assert(a.head == NULL);
  assert(a.tail == NULL);
  a.addFront(2);
  assert(a.head->data == 2);
  assert(a[0] == 2);
  assert(a.head->next == NULL);
  assert(a.head->prev == NULL);
  assert(a.getSize() == 1);
  a.remove(2);
  assert(a.head == NULL);
  assert(a.getSize() == 0);
  for (int i = 0; i < 3; i++) {
    a.addFront(i);
  }
  assert(a.getSize() == 3);
  IntList b(a);
  IntList c;
  c = a;
  for (int i = 0; i < 3; i++) {
    assert(a[i] == 2 - i);
    assert(b[i] == 2 - i);
    assert(c[i] == 2 - i);
    assert(a.find(i) == 2 - i);
  }
  assert(b.getSize() == c.getSize());
  assert(a.tail->next == NULL);
  assert(a.head->prev == NULL);
  assert(a.remove(4) == false);
  for (int i = 0; i < 3; i++) {
    assert(a.remove(i) == true);
  }
  assert(a.getSize() == 0);
  for (int i = 0; i < 3; i++) {
    a.addBack(i);
  }
  assert(a.getSize() == 3);

  for (int i = 0; i < 3; i++) {
    assert(a[i] == i);
    assert(a.find(i) == i);
  }
  a.remove(1);
  assert(a.head->next->data == 2);
  assert(a.tail->prev->data == 0);
  b.~IntList();
}

int main(void) {
  testList();
  return EXIT_SUCCESS;
}
