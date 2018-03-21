#include "../src/Header.cpp"
#include <vector>

namespace Utils {
Header readDataFile(std::string baseName);
std::vector<unsigned char**> readRawFile(std::string baseName);
unsigned char** readSlice(Header h, int index);
void writeSliceToFile(unsigned char** slice,Header h, int index);
} /* Utils */
