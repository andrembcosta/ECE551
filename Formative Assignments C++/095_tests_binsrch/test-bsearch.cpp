#include <assert.h>

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "CountedIntFn.h"
#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high);

void check(Function<int, int> * f,
           int low,
           int high,
           int expected_ans,
           const char * mesg) {
  unsigned max = 0;
  if (low >= high) {
    max = 1;
  }
  else {
    max = (unsigned)(log2(high - low) + 0.5) + 1;
  }
  //  std::cout << max << std::endl;
  CountedIntFn F(max, f, mesg);
  assert(binarySearchForZero(&F, low, high) == expected_ans);
}

class LinearFunction : public Function<int, int> {
  double zero;
  int slope;

 public:
  LinearFunction(double z, int s) : zero(z), slope(s) {}

  virtual int invoke(int arg) { return slope * (arg - zero); }
};

int main(void) {
  LinearFunction _2x2(1, 2);    //function with integer root
  LinearFunction _2x1(0.5, 2);  //function without integer root
  std::cout << "1" << std::endl;
  check(&_2x2, -100, 100, 1, "with root large interval");  //large interval
  std::cout << "2" << std::endl;
  check(&_2x2, -2, 2, 1, "with root small interval");  //small interval
  std::cout << "3" << std::endl;
  check(&_2x2, -100, -49, -50, "with root negtives");  //only negatives
  std::cout << "4" << std::endl;
  check(&_2x2, 50, 100, 50, "with root positives");  //only positives
  std::cout << "5" << std::endl;
  check(&_2x1, -100, 100, 0, "no root large int");
  std::cout << "6" << std::endl;
  check(&_2x1, -2, 2, 0, "no root small int");
  std::cout << "7" << std::endl;
  check(&_2x1, 2, 2, 2, "no root low=high");  //low = high
  std::cout << "8" << std::endl;
  return EXIT_SUCCESS;
}
