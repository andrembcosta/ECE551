#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> streamToVector(std::istream & s) {
  std::vector<std::string> linesVector;
  std::string thisLine;
  while (std::getline(s, thisLine)) {
    linesVector.push_back(thisLine);
  }
  return linesVector;
}

void printer(std::vector<std::string> v) {
  for (size_t i = 0; i < v.size(); i++) {
    std::cout << v[i] << std::endl;
  }
}

int main(int argc, char ** argv) {
  if (argc == 1) {
    //read from stdin
    std::vector<std::string> linesVector = streamToVector(std::cin);
    std::sort(linesVector.begin(), linesVector.end());
    printer(linesVector);
  }
  else {
    for (int i = 1; i < argc; i++) {
      std::ifstream thisFile(argv[i]);
      if (thisFile.fail()) {
        std::cout << "Could not open file" << std::endl;
        return EXIT_FAILURE;
      }
      std::vector<std::string> linesVector = streamToVector(thisFile);
      std::sort(linesVector.begin(), linesVector.end());
      printer(linesVector);
      thisFile.close();
    }
  }
  return EXIT_SUCCESS;
}
