#include "../src/Header.cpp"
#include <vector>

namespace Utils {
unsigned char** VectorDifference(Header h,std::vector<unsigned char**> volume,int i, int j);
Header readDataFile(std::string baseName);
std::vector<unsigned char**> readRawFiles(Header h);
unsigned char** readSlice(Header h, int index);
void writeSliceToFile(unsigned char** slice,Header h, int index);
unsigned char** extractAcrossSlices(Header h,std::vector<unsigned char**> volume,int row);
} /* Utils */
