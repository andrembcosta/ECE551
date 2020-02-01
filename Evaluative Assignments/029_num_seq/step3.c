// This file is for Step 3.
// You should do
//  Step 3 (A): write seq3
//  Step 3 (B): write main to test seq3
//  Step 3 (C): write countEvenInSeq3Range
//  Step 3 (D): add test cases to main to test countEvenInSeq3Range
//
// Be sure to #include any header files you need!

#include <stdio.h>
#include <stdlib.h>

//function seq3 computes the given sequence given arguments x
//and y

int seq3(int x, int y) {
  return (x + 2) * (y - 3) + 6;
}

//function test tests the implementation to see if it returns
//the expected answer for a pair (a,b). The user must give the
//expected answer as a paramenter to test (parameter ans).
//The function will return 1 if seq3 finds the expected answer and
//0 otherwise.

int test(int a, int b, int ans) {
  int r = seq3(a, b);
  printf("seq3(%d,%d) = %d\n", a, b, r);
  return !(r - ans);
}

//this function counts the number of even values of seq3 inside a
//"rectangle". That is, the number of even values inside a region
//delimited by the coordinates xLow, xHi, yLow, yHi.
int countEvenInSeq3Range(int xLow, int xHi, int yLow, int yHi) {
  if (xLow >= xHi || yLow >= yHi) {
    return 0;
  }
  if (xLow == xHi - 1) {
    int totalEven = 0;
    for (int i = yLow; i < yHi; i++) {
      totalEven = totalEven + !(seq3(xLow, i) % 2);
    }
    return totalEven;
  }
  else {
    return countEvenInSeq3Range(xLow, xHi - 1, yLow, yHi) +
           countEvenInSeq3Range(xHi - 1, xHi, yLow, yHi);
  }
}

//the main function tests the implementation of seq3 for many different
//arguments by calling test. It also tests the counteveninseq3range function
//by printing its return values for multiple rectangles

int main(void) {
  int isGood;
  //test large negative numbers
  isGood = test(-132, -70, 9496);
  if (isGood == 0) {
    return EXIT_FAILURE;
  }
  //test small negative numbers
  isGood = test(-3, -5, 14);
  if (isGood == 0) {
    return EXIT_FAILURE;
  }
  //test a "root" and a large number
  isGood = test(-2, 1000000, 6);
  if (isGood == 0) {
    return EXIT_FAILURE;
  }
  //test the other "root" and a large number
  isGood = test(2000000, 3, 6);
  if (isGood == 0) {
    return EXIT_FAILURE;
  }
  //test x=y=0
  isGood = test(0, 0, 0);
  if (isGood == 0) {
    return EXIT_FAILURE;
  }
  //test two small positive numbers
  isGood = test(1, 5, 12);
  if (isGood == 0) {
    return EXIT_FAILURE;
  }
  //test two large positive numbers
  isGood = test(898, 1003, 900006);
  if (isGood == 0) {
    return EXIT_FAILURE;
  }

  //I really don't know whay emacs is formattint the following calls
  //to printf in this weird way...

  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",
         0,
         10,
         0,
         10,
         countEvenInSeq3Range(0, 10, 0, 10));
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",
         -5,
         0,
         -5,
         0,
         countEvenInSeq3Range(-5, 0, -5, 0));
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",
         2,
         2,
         0,
         10,
         countEvenInSeq3Range(2, 2, 0, 10));
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",
         0,
         10,
         2,
         2,
         countEvenInSeq3Range(0, 10, 2, 2));
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",
         0,
         10,
         -1,
         -5,
         countEvenInSeq3Range(0, 10, -1, -5));
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",
         -1,
         -5,
         0,
         10,
         countEvenInSeq3Range(-1, -5, 0, 10));
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",
         0,
         1,
         0,
         1,
         countEvenInSeq3Range(0, 1, 0, 1));
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",
         1,
         2,
         0,
         1,
         countEvenInSeq3Range(1, 2, 0, 1));

  return EXIT_SUCCESS;
}
