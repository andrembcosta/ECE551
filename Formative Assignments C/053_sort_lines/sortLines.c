#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

char ** streamToArray(FILE * stream, size_t * count) {
  size_t sz = 0;
  ssize_t len = 0;
  char * line = NULL;
  size_t i = 0;
  char ** stringArray = NULL;
  while ((len = getline(&line, &sz, stream)) >= 0) {
    stringArray = realloc(stringArray, (i + 1) * sizeof(*stringArray));
    stringArray[i] = line;
    line = NULL;
    i++;
  }
  free(line);
  *count = i;
  return stringArray;
}

void printer(char ** stringArray, size_t * count) {
  for (size_t i = 0; i < *count; i++) {
    printf("%s", stringArray[i]);
  }
}

void freer(char ** stringArray, size_t * count) {
  for (size_t i = 0; i < *count; i++) {
    free(stringArray[i]);
  }
  free(stringArray);
}

int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!
  size_t zero = 0;
  size_t * count = &zero;
  if (argc == 1) {
    //printf("Please, enter the text that should be sorted: (Ctrl-D for EOF) \n");
    //read from stdin
    char ** stringArray = streamToArray(stdin, count);
    sortData(stringArray, *count);
    printer(stringArray, count);
    freer(stringArray, count);
    return EXIT_SUCCESS;
  }
  else {
    //read from files
    for (int i = 1; i < argc; i++) {
      FILE * stream = fopen(argv[i], "r");
      if (stream == NULL) {
        perror("Could not open the file\n");
        return EXIT_FAILURE;
      }
      char ** stringArray = streamToArray(stream, count);
      sortData(stringArray, *count);
      printer(stringArray, count);
      freer(stringArray, count);
      if (fclose(stream) != 0) {
        printf("Could not close the file\n");
        return EXIT_FAILURE;
      }
    }
  }
  return EXIT_SUCCESS;
}
