#include "../src/Header.cpp"
#include <vector>

namespace Utils {
  Header readDataFile(std::string baseName);
  std::vector<unsigned char**> readRawFile(std::string baseName);
  unsigned char** readImage(std::string baseName, int index);
} /* Utils */
