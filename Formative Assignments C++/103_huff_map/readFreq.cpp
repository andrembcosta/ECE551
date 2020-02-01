#include "readFreq.h"

#include <stdio.h>

#include <cstdlib>
#include <fstream>

void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  //WRITE ME!
  std::ifstream file(fname);
  if (file.fail()) {
    std::cerr << "Could not open file" << std::endl;
    return NULL;
  }
  uint64_t * freqArray = new uint64_t[257]();
  char c;
  while (file.get(c)) {
    freqArray[(int)(unsigned char)c]++;
  }
  freqArray[256] = 1;
  file.close();
  return freqArray;
}
