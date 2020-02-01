#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  char * suffix = ".counts";
  char * outname = malloc((strlen(inputName) + strlen(suffix) + 1) * (sizeof(*outname)));
  for (unsigned long i = 0; i < strlen(inputName); i++) {
    outname[i] = inputName[i];
  }
  for (unsigned long i = 0; i <= strlen(suffix); i++) {
    outname[i + strlen(inputName)] = suffix[i];
  }
  return outname;
}
