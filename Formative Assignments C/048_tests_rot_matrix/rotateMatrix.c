#include <stdio.h>
#include <stdlib.h>

void rotateStream(FILE * stream, int * array) {
  int c;
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 11; j++) {
      c = fgetc(stream);
      if (j == 10 && c != 10) {
        *array = -1;
        printf("some line doesn't end with newline after 10 characters\n");
        return;
      }
      if (j < 10 && c != 10) {
        *(array + j * 10 + 9 - i) = c;
      }
      if (j < 10 && c == 10) {
        *array = -1;
        printf("found a newline character in the middle of a line\n");
        return;
      }
    }
  }
  c = fgetc(stream);
  if (c != EOF) {
    *array = -1;
    printf("your file doesn't end after 10 lines\n");
    return;
  }
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "tried to pass a wrong number of arguments\n");
    return EXIT_FAILURE;
  }
  FILE * matrix = fopen(argv[1], "r");
  if (matrix == NULL) {
    fprintf(stderr, "couldn't open your file\n");
    return EXIT_FAILURE;
  }
  int zeros[10][10] = {{0}};
  int * rotatedMatrix = &zeros[0][0];
  rotateStream(matrix, rotatedMatrix);
  if (*rotatedMatrix == -1) {
    fprintf(stderr, "rotateStream found an error, probably ill-sized matrices\n");
    return EXIT_FAILURE;
  }
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 11; j++) {
      if (j == 10) {
        printf("\n");
      }
      else {
        printf("%c", *(rotatedMatrix + 10 * i + j));
      }
    }
  }
  if (fclose(matrix) != 0) {
    fprintf(stderr, "Couldn't close the file");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
