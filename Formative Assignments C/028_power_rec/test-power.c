#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);

int testPower(unsigned a, unsigned b, unsigned ans) {
  if (power(a, b) == ans) {
    return 1;
  }
  else {
    return 0;
  }
}

int main(void) {
  int isGood;
  //test for wrong types

  //test for small numbers and powers
  for (int i = 0; i < 4; i++) {
    isGood = testPower(i, 0, 1);
    if (isGood == 0) {
      printf("Buggy code");
      return EXIT_FAILURE;
    }
  }
  for (int i = 0; i < 4; i++) {
    isGood = testPower(i, 1, i);
    if (isGood == 0) {
      printf("Buggy code");
      return EXIT_FAILURE;
    }
  }
  for (int i = 0; i < 4; i++) {
    isGood = testPower(i, 2, i * i);
    if (isGood == 0) {
      printf("Buggy code");
      return EXIT_FAILURE;
    }
  }
  for (int i = 0; i < 4; i++) {
    isGood = testPower(i, 3, i * i * i);
    if (isGood == 0) {
      printf("Buggy code");
      return EXIT_FAILURE;
    }
  }
  //test for large numbers and small powers
  for (int i = 0; i < 4; i++) {
    int expectedAns = 1;
    switch (i) {
      case 0:
        expectedAns = 1;
        break;
      case 1:
        expectedAns = 57;
        break;
      case 2:
        expectedAns = 57 * 57;
        break;
      case 3:
        expectedAns = 57 * 57 * 57;
        break;
    }
    isGood = testPower(57, i, expectedAns);
    if (isGood == 0) {
      printf("Buggy code");
      return EXIT_FAILURE;
    }
  }
  //test for large numbers and large powers
  isGood = testPower(11, 9, 2357947691);
  if (isGood == 0) {
    printf("Buggy code");
    return EXIT_FAILURE;
  }
  printf("Nice code");
  return EXIT_SUCCESS;
}
