#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

int test(int * array, size_t n, int ans) {
  return !(maxSeq(array, n) - ans);
}

int main(void) {
  int isGood = 1;
  int testArray1[] = {7};
  size_t size = 1;
  isGood = test(testArray1, size, 1);
  if (isGood == 0) {
    return EXIT_FAILURE;
  }
  int testArray2[] = {1, 2, 3, 3, 4, 5};
  size = 6;
  isGood = test(testArray2, size, 3);
  if (isGood == 0) {
    return EXIT_FAILURE;
  }
  int testArray3[0] = {};
  size = 0;
  isGood = test(testArray3, size, 0);
  if (isGood == 0) {
    return EXIT_FAILURE;
  }
  int testArray4[] = {3, 2, 1};
  size = 3;
  isGood = test(testArray4, size, 1);
  if (isGood == 0) {
    return EXIT_FAILURE;
  }
  int testArray5[] = {1, 2, 3};
  size = 3;
  isGood = test(testArray5, size, 3);
  if (isGood == 0) {
    return EXIT_FAILURE;
  }
  int testArray6[] = {0xFFFFFFFF, 2};
  size = 2;
  isGood = test(testArray6, size, 2);
  if (isGood == 0) {
    return EXIT_FAILURE;
  }
  int testArray7[] = {1, 2, 2, 1, 2, 3};
  size = 6;
  isGood = test(testArray7, size, 3);
  if (isGood == 0) {
    return EXIT_FAILURE;
  }
  printf("Seems Good\n");
  return EXIT_SUCCESS;
}
