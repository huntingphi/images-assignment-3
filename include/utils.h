#include <string>
#include <vector>
#include "Metadata.h"
// #ifndef VOLIMAGE
//   #define VOLIMAGE
//   #include "volimage.h"
//
// #endif

namespace Utils {
enum class Operations {DIFF_MAP,EXTRACT,BUILD,EXTRACT_ACROSS_SLICES,FAIL};
Operations parse_args(int argc, char* argv[]);
unsigned char** VectorDifference(Metadata h,std::vector<unsigned char**> volume,int i, int j);
Metadata readDataFile(std::string baseName);
std::vector<unsigned char**> readRawFiles(Metadata h);
unsigned char** readSlice(Metadata h, int index);
void writeSliceToFile(unsigned char** slice,Metadata h, int index);
unsigned char** extractAcrossSlices(Metadata h,std::vector<unsigned char**> volume,int row);
} /* Utils */
