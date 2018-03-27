#include <string>
#include <iostream>
#include <vector>
#include "../include/volimage.h"
#include "../include/utils.h"
#include "../include/Metadata.h"



VolImage::VolImage(){
        width = 0;
        height = 0;
        baseName = "";
}
VolImage::~VolImage(){
        // destructor - define in .cpp file
}


// populate the object with images in stack and
//set member variables define in .cpp
bool VolImage::readImages(std::string baseName){
        Metadata md = Utils::readDataFile(baseName);
        slices = Utils::readRawFiles(md);
        width = md.width;
        height = md.height;
        baseName = md.baseName;
}


void VolImage::diffmap(int sliceI, int sliceJ, std::string output_prefix){
        Metadata image_data = Utils::readDataFile(baseName);
        Metadata output_data(output_prefix,width,height,1);
        Utils::writeSliceToFile(Utils::VectorDifference(image_data,slices,sliceI,sliceJ),output_data,0);
        // extract slice sliceId and write to output - define in .cpp

}
void VolImage::extract(int sliceId, std::string output_prefix){
        Metadata output_data(output_prefix,width,height,1);
        Utils::writeSliceToFile(slices[sliceId],output_data,sliceId);
        // number of bytes uses to store image data bytes
        //and pointers (ignore vector<> container, dims etc)
}

void VolImage::extractAcross(int sliceId, std::string output_prefix){
        Metadata image_data = Utils::readDataFile(baseName);
        Metadata output_data(output_prefix,width,height,1);
        Utils::writeSliceToFile(Utils::extractAcrossSlices(image_data,slices,sliceId),output_data,0);
        // number of bytes uses to store image data bytes
        //and pointers (ignore vector<> container, dims etc)
}

int VolImage::volImageSize(void){
        //TODO check if this works
        return sizeof(slices);
}
