#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n) {
  if (n <= 0) {
    return 0;
  }

  size_t currentMax = 1;
  size_t currentSeqSize = 1;

  for (unsigned i = 0; i < n - 1; i++) {
    if (array[i] < array[i + 1]) {
      currentSeqSize++;
      if (currentSeqSize > currentMax) {
        currentMax = currentSeqSize;
      }
    }
    else {
      currentSeqSize = 1;
    }
  }

  return currentMax;
}
