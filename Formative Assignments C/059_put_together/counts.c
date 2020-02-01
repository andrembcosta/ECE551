#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
counts_t * createCounts(void) {
  //WRITE ME
  //one_count_t * individualCounters = malloc(sizeof(*individualCounters));
  //individualCounters->value = NULL;
  //individualCounters->reps = 0;

  counts_t * myCount = malloc(sizeof(*myCount));
  myCount->countsArray = NULL;
  myCount->lenght = 0;
  myCount->unknowns = 0;

  return myCount;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME

  if (name == NULL) {
    c->unknowns++;
    return;
  }

  for (unsigned long i = 0; i < c->lenght; i++) {
    if (!strcmp(c->countsArray[i].value, name)) {
      c->countsArray[i].reps++;
      return;
    }
  }

  c->countsArray = realloc(c->countsArray, (c->lenght + 1) * sizeof(*c->countsArray));
  c->countsArray[c->lenght].value = strdup(name);
  c->countsArray[c->lenght].reps = 1;
  c->lenght++;
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  for (unsigned long i = 0; i < c->lenght; i++) {
    fprintf(outFile, "%s: %d\n", c->countsArray[i].value, c->countsArray[i].reps);
  }
  if (c->unknowns > 0) {
    fprintf(outFile, "<unknown> : %lu\n", c->unknowns);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for (unsigned long i = 0; i < c->lenght; i++) {
    free(c->countsArray[i].value);
  }
  free(c->countsArray);
  free(c);
}
