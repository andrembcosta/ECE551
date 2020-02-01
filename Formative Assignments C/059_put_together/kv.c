#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void replace_char(char * str, char find, char replace) {
  char * current_pos = strchr(str, find);
  while (current_pos) {
    *current_pos = replace;
    current_pos = strchr(current_pos, find);
  }
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * KVstream = fopen(fname, "r");
  if (KVstream == NULL) {
    printf("readKVs couldn't open yout file\n");
    return NULL;
  }
  int nLines = 0;
  char * curr = NULL;
  kvpair_t * pairs = NULL;
  size_t linecap;
  while (getline(&curr, &linecap, KVstream) >= 0) {
    pairs = realloc(pairs, (nLines + 1) * sizeof(*pairs));
    char * divider = strchr(curr, 61);
    if (divider == NULL) {
      printf("Some line doesn't contain a '='\n");
      return NULL;
    }
    *divider = '\0';
    replace_char(divider + 1, '\n', '\0');
    pairs[nLines].key = curr;
    pairs[nLines].value = divider + 1;
    nLines++;
    curr = NULL;
  }
  free(curr);
  kvarray_t * ans = malloc(sizeof(*ans));
  ans->array = pairs;
  ans->lenght = nLines;

  if (fclose(KVstream) != 0) {
    printf("Couldn't close the file\n");
    return NULL;
  }

  return ans;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for (size_t i = 0; i < pairs->lenght; i++) {
    free(pairs->array[i].key);
  }
  free(pairs->array);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for (size_t i = 0; i < pairs->lenght; i++) {
    printf("key = '%s' value = '%s'\n", pairs->array[i].key, pairs->array[i].value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for (size_t i = 0; i < pairs->lenght; i++) {
    int comp = strcmp(key, pairs->array[i].key);
    if (comp == 0) {
      return pairs->array[i].value;
    }
  }

  return NULL;
}
