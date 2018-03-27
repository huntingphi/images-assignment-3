#include "../include/Metadata.h"
#include <string>
#include <vector>

namespace Utils {
unsigned char** VectorDifference(Metadata h,std::vector<unsigned char**> volume,int i, int j);
Metadata readDataFile(std::string baseName);
std::vector<unsigned char**> readRawFiles(Metadata h);
unsigned char** readSlice(Metadata h, int index);
void writeSliceToFile(unsigned char** slice,Metadata h, int index);
unsigned char** extractAcrossSlices(Metadata h,std::vector<unsigned char**> volume,int row);
} /* Utils */
