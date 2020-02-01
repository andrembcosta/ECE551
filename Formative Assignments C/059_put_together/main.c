#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  //fopen(filename)
  FILE * thisFile = fopen(filename, "r");
  if (thisFile == NULL) {
    printf("countFile couldn't open your file\n");
    return NULL;
  }
  //getlines + realloc to make array
  char ** keys = NULL;
  char * curr = NULL;
  size_t linecap;
  size_t i = 0;
  while (getline(&curr, &linecap, thisFile) >= 0) {
    keys = realloc(keys, (i + 1) * sizeof(*keys));
    keys[i] = curr;
    replace_char(keys[i], '\n', '\0');
    curr = NULL;
    i++;
  }
  free(curr);
  if (fclose(thisFile)) {
    printf("countFile couldn't close your file\n");
    return NULL;
  }
  //use lookupValue to translate array to newarray
  char ** values = NULL;
  for (size_t j = 0; j < i; j++) {
    values = realloc(values, (j + 1) * sizeof(*values));
    values[j] = lookupValue(kvPairs, keys[j]);
    free(keys[j]);
  }
  free(keys);

  //check main58 to generate c
  counts_t * c = createCounts();
  for (size_t k = 0; k < i; k++) {
    addCount(c, values[k]);
  }
  free(values);

  return c;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  if (argc <= 2) {
    fprintf(stderr, "this function need at least two files as arguments\n");
    return EXIT_FAILURE;
  }
  kvarray_t * kv = readKVs(argv[1]);
  //read the key/value pairs from the file named by argv[1] (call the result kv)

  //count from 2 to argc (call the number you count i)
  for (int i = 2; i < argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t * c = countFile(argv[i], kv);
    //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]);
    //open the file named by outName (call that f)
    FILE * f = fopen(outName, "w");
    //write exception is fopen fails
    printCounts(c, f);
    //print the counts from c into the FILE f
    if (fclose(f)) {
      printf("main couldn't close one of your files\n");
      return EXIT_FAILURE;
    }
    //close f

    //free the memory for outName and c
    freeCounts(c);
    free(outName);
  }
  //free the memory for kv
  freeKVs(kv);
  return EXIT_SUCCESS;
}
