#include <string>
#include <iostream>
#include <vector>
#include "../include/volimage.h"



int VolImage::mockMethod(){
  // Method to test that the test framework works;

  return 1;
}



  // private members

  int width, height;
  // width and height of image stack

  std::vector<unsigned char**> slices;
  // data for each slice, in order


  // public members

  VolImage::VolImage(){
    // default constructor - define in .cpp

  }
  VolImage::~VolImage(){
    // destructor - define in .cpp file
    // populate the object with images in stack and
    //set member variables define in .cpp

  }



  bool VolImage::readImages(std::string baseName){
    // compute difference map and write out;  define in .cpp

  }


  void VolImage::diffmap(int sliceI, int sliceJ, std::string output_prefix){
    // extract slice sliceId and write to output - define in .cpp

  }
  void VolImage::extract(int sliceId, std::string output_prefix){
    // number of bytes uses to store image data bytes
    //and pointers (ignore vector<> container, dims etc)
  }

  int VolImage::volImageSize(void){
    // define in .cpp

  }
