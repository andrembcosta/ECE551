#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  if (low >= high - 1) {
    return low;
  }
  int guess = (low + high) / 2;
  int eval = f->invoke(guess);
  if (eval > 0) {
    return binarySearchForZero(f, low, guess);
  }
  if (eval < 0) {
    return binarySearchForZero(f, guess, high);
  }
  else {
    return guess;
  }
}
