#include <iostream>

#include "bstmap.h"
#include "map.h"

int main(void) {
  BstMap<int, int> b;
  b.add(1, 1);
  //std::cout << b.root->key << std::endl;
  b.add(3, 3);
  //std::cout << b.root->right->key << std::endl;
  //b.add(20, 20);
  //b.add(4, 4);
  //b.add(15, 15);
  //b.add(10, 10);
  b.add(-1, -1);
  b.add(-4, -4);

  BstMap<int, int> c(b);

  //std::cout << b.lookup(3) << std::endl;
  c.remove(1);
  //c.remove(20);
  //c.remove(3);

  //c.add(3, 4);

  BstMap<int, int> d;
  d = c;
  d = d;

  std::cout << c.root->key << std::endl;
  std::cout << c.lookup(-4) << c.lookup(-1) << std::endl;
  //std::cout << d.lookup(4) << d.lookup(2) << d.lookup(1) << std::endl;

  return 0;
}
