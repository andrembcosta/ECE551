#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int maxIndex(int * array, int n) {
  if (n <= 0) {
    return -1;
  }
  int * largest = array;
  int ans = 0;
  for (int i = 0; i < n; i++) {
    if (*largest < array[i]) {
      largest = &array[i];
      ans = i;
    }
  }
  return ans;
}

int findLetter(FILE * stream) {
  int freq[26] = {0};
  int c;
  int index;
  while ((c = fgetc(stream)) != EOF) {
    if (isalpha(c)) {
      index = c - 'a';
      freq[index]++;
    }
  }
  return maxIndex(freq, 26);
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr,
            "We can't operate on this number of arguments. You should have exactly one "
            "file to be decripted");
    return EXIT_FAILURE;
  }
  FILE * encText = fopen(argv[1], "r");
  if (encText == NULL) {
    fprintf(stderr, "Couldn't open file");
    return EXIT_FAILURE;
  }
  int keyLetter = findLetter(encText);
  int key = (22 + keyLetter) % 26;
  if (fclose(encText) != 0) {
    fprintf(stderr, "Couldn't close file");
    return EXIT_FAILURE;
  }
  printf("%d\n", key);
  return EXIT_SUCCESS;
}
