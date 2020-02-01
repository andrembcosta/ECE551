// This file is for Step 1.
// You should do
//  Step 1 (A): write seq1
//  Step 1 (B): write main to test seq1
//  Step 1 (C): write printSeq1Range
//  Step 1 (D): add test cases to main to test printSeq1Range
//
// Be sure to #include any header files you need!
#include <stdio.h>
#include <stdlib.h>

//function to compute the sequence
int seq1(int x) {
  return (4 * x - 3);
}

//function to test the implementation of seq1
//to test if seq1 is correct at argument a, pass
//a and the correct answer(ans) to this function
//it returns 1 if seq1 returns the correct value
//or 0 if it doesnt.
int test(int a, int ans) {
  int r = seq1(a);
  printf("seq1(%d) = %d\n", a, r);
  return !(r - ans);
}

//function to print a given interval of values in
//the sequence seq1, the user must pass the lower
//bound(low) and upper bound(high) of the interval
void printSeq1Range(int low, int high) {
  if (low >= high) {
    printf("\n");
  }
  else {
    for (int i = low; i < high - 1; i++) {
      int v = seq1(i);
      printf("%d, ", v);
    }
    int final = seq1(high - 1);  //the final term is treated differently
    //because it is not followed by comma
    printf("%d\n", final);
  }
}

//main function will test the implementation of seq1 using the function test
//and the implementation of printSeq1range at many different parameters
int main(void) {
  int isGood;
  //test large negative number
  isGood = test(-132, -531);
  if (isGood == 0) {
    return EXIT_FAILURE;
  }
  //test small negative number
  isGood = test(-3, -15);
  if (isGood == 0) {
    return EXIT_FAILURE;
  }
  //test x=0
  isGood = test(0, -3);
  if (isGood == 0) {
    return EXIT_FAILURE;
  }
  //test x=1
  isGood = test(1, 1);
  if (isGood == 0) {
    return EXIT_FAILURE;
  }
  //test small positive number
  isGood = test(4, 13);
  if (isGood == 0) {
    return EXIT_FAILURE;
  }
  //test large positive number
  isGood = test(2579, 10313);
  if (isGood == 0) {
    return EXIT_FAILURE;
  }
  printf("printSeq1Range(%d, %d)\n", 0, 10);
  printSeq1Range(0, 10);
  printf("printSeq1Range(%d, %d)\n", -3, 7);
  printSeq1Range(-3, 7);
  printf("printSeq1Range(%d, %d)\n", 0, 0);
  printSeq1Range(0, 0);
  printf("printSeq1Range(%d, %d)\n", -7, -2);
  printSeq1Range(-7, -2);
  printf("printSeq1Range(%d, %d)\n", -2, -7);
  printSeq1Range(-2, -7);

  return EXIT_SUCCESS;
}
