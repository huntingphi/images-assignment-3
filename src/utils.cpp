#include "../src/Header.cpp"
#include "../include/utils.h"
#include <vector>
#include <iostream>
#include <fstream>


using namespace Utils;

Header readDataFile(std::string baseName){


}

std::vector<unsigned char**> readRawFiles(Header h){
  std::string baseName = h.baseName;
  int number_of_images = h.number_of_images;
  std::vector<unsigned char**> slices;
  for (size_t i = 0; i < number_of_images; i++) {
    slices.push_back(readImage(baseName,int(i)));
    // std::string line;
    // std::string filepath = "../assets/"+baseName;
    // std::ifstream  myfile(filepath);
    // if (myfile.is_open())
    // {
    //   while ( getline (myfile,line) )
    //   {
    //     std::cout << line << '\n';
    //   }
    //   myfile.close();
    // }
    //
    // else std::cout << "Unable to open file";

  }

  return slices;
}



unsigned char** readImage(Header h, int index){
  std::string baseName = h.baseName;
  int width = h.width;
  int height = h.height;
  std::string filepath = "../assets/"+baseName;
  std::ifstream  raw_image(filepath);
  //Make a pointer to a pointer that points to a char
  unsigned char** image;
  //Assign a pointer to the first element of the array(which is a pointer)
  // to the image**
  image = new unsigned char* [height];
  for (int i = 0; i < height; i++) {
    image[i] = new unsigned char[width];
  }

}
