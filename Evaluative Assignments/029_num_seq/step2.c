// This file is for Step 2.
// You should do
//  Step 2 (A): write seq2
//  Step 2 (B): write main to test seq2
//  Step 2 (C): write sumSeq2
//  Step 2 (D): add test cases to main to test sumSeq2
//
// Be sure to #include any header files you need!

#include <stdio.h>
#include <stdlib.h>

//function seq2 computes the given sequence
int seq2(int x) {
  if (x % 4 == 2 || x % 4 == -2) {
    return 2 * x;
  }
  else {
    return (x + 1) * (x + 1) + x;
  }
}

//function test will test seq2 at a given argument (a)
//to see if it finds the given answer (ans). Return 1
//if seq2 returns the expected value, 0 otherwise.
int test(int a, int ans) {
  int r = seq2(a);
  printf("seq2(%d) = %d\n", a, r);
  return !(r - ans);
}

//function sumSeq2 will compute the sum of consecutive elements
//in seq2. The user should pass the lower bound of the interval
//of elements (low) and the upper bound (high). This implementation
//is recursive
int sumSeq2(int low, int high) {
  if (low >= high) {
    return 0;
  }
  else {
    return sumSeq2(low, high - 1) + seq2(high - 1);
  }
}

//function main tests the implementation of seq2 at various
//arguments by calling test. It also tests sumSeq2 by print
//its return values for many different intervals.

int main(void) {
  int isGood;
  //test large negative number not 4k+2
  isGood = test(-132, 17029);
  if (isGood == 0) {
    return EXIT_FAILURE;
  }
  //test large negative number 4k+2
  isGood = test(-250, -500);
  if (isGood == 0) {
    return EXIT_FAILURE;
  }

  //test small negative number not 4k+2
  isGood = test(-3, 1);
  if (isGood == 0) {
    return EXIT_FAILURE;
  }
  //test small negative number  4k+2
  isGood = test(-2, -4);
  if (isGood == 0) {
    return EXIT_FAILURE;
  }
  //test x=0
  isGood = test(0, 1);
  if (isGood == 0) {
    return EXIT_FAILURE;
  }
  //test x=1
  isGood = test(1, 5);
  if (isGood == 0) {
    return EXIT_FAILURE;
  }
  //test small positive number not 4k+2
  isGood = test(4, 29);
  if (isGood == 0) {
    return EXIT_FAILURE;
  }
  //test small positive number 4k+2
  isGood = test(2, 4);
  if (isGood == 0) {
    return EXIT_FAILURE;
  }
  //test large positive number not 4k+2
  isGood = test(1051, 1107755);
  if (isGood == 0) {
    return EXIT_FAILURE;
  }
  //test large positive number 4k+2
  isGood = test(2502, 5004);
  if (isGood == 0) {
    return EXIT_FAILURE;
  }
  printf("sumSeq2(%d, %d) = %d\n", 0, 10, sumSeq2(0, 10));
  printf("sumSeq2(%d, %d) = %d\n", -3, 7, sumSeq2(-3, 7));
  printf("sumSeq2(%d, %d) = %d\n", 0, 0, sumSeq2(0, 0));
  printf("sumSeq2(%d, %d) = %d\n", -7, -2, sumSeq2(-7, -2));
  printf("sumSeq2(%d, %d) = %d\n", -2, -7, sumSeq2(-2, -7));

  return EXIT_SUCCESS;
}
