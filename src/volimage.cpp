#include <string>
#include <iostream>
#include <vector>
#include "../include/volimage.h"



int VolImage::mockMethod(){
        // Method to test that the test framework works;

        return 1;
}

// public members

VolImage::VolImage(){
        width = 0;
        height = 0;

}
VolImage::~VolImage(){
        // destructor - define in .cpp file
        // populate the object with images in stack and
        //set member variables define in .cpp

}



bool VolImage::readImages(std::string baseName){


}


void VolImage::diffmap(int sliceI, int sliceJ, std::string output_prefix){
        // extract slice sliceId and write to output - define in .cpp

}
void VolImage::extract(int sliceId, std::string output_prefix){
        // number of bytes uses to store image data bytes
        //and pointers (ignore vector<> container, dims etc)
}

int VolImage::volImageSize(void){
        //TODO check if this works
        return sizeof(slices);
}
