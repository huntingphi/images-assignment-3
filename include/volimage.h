#include <vector>
#include <string>
// #ifndef UTILS
//   #define UTILS
//   #include "utils.h"
// #endif
#include "utils.h"

#include "Metadata.h"
class VolImage {
private:
// private members
int width, height;
std::string baseName;
// width and height of image stack
std::vector<unsigned char**> slices;
// data for each slice, in order
public:
// public members
int i, j,num_imgs;
std::string output_name;
VolImage();
// default constructor - define in .cpp
~VolImage();
// destructor - define in .cpp file

Metadata readDataFile(std::string baseName);

// populate the object with images in stack and
//set member variables define in .cpp
bool readImages(std::string baseName);


unsigned char** readSlice(Metadata h, int index);

void writeSliceToFile(unsigned char** slice, Metadata h, int index);

void writeSliceToFile(unsigned char** slice, Metadata h, std::string output_name);

// compute difference map and write out;  define in .cpp
void diffmap(int sliceI, int sliceJ, std::string output_prefix);
// extract slice sliceId and write to output - define in .cpp

unsigned char** VectorDifference(Metadata h,std::vector<unsigned char**> volume,int i, int j);

unsigned char** extractAcrossSlices(Metadata h,std::vector<unsigned char**> volume,int row);


void extract(int sliceId, std::string output_prefix);
//
//
void extractAcross(int sliceId, std::string output_prefix);
// number of bytes uses to store image data bytes
//and pointers (ignore vector<> container, dims etc)
int volImageSize(void);
// define in .cpp
int volImageCount(void);



std::vector<unsigned char**> getSlices(){
        return slices;
}

};
