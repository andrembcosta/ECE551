#include <stdint.h>

#include <fstream>

uint64_t * readFrequencies(const char * fname) {
  std::ifstream file(fname);
  uint64_t * freqArray = new uint64_t[257]();
  char c;
  while (file.get(c)) {
    freqArray[(int)c]++;
  }
  freqArray[256] = 1;
  file.close();
  return freqArray;
}
