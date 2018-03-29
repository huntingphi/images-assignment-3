#include <string>
#include <iostream>
#include <vector>
#include <fstream>

#ifndef HEADERFILE
  #define HEADERFILE
  #include "../include/volimage.h"
#endif





VolImage::VolImage(){
        width = 0;
        height = 0;
        baseName = "";
}
VolImage::~VolImage(){
        // destructor - define in .cpp file
}

Metadata VolImage::readDataFile(std::string baseName){
        std::string filepath = "assets/"+baseName+".data";
        std::ifstream dataFile(filepath);
        std::string name = baseName;
        int width, height, num_imgs;
        dataFile >> width;
        dataFile >> height;
        dataFile >> num_imgs;
        Metadata h(name,width,height,num_imgs);
        return h;
}


// populate the object with images in stack and
//set member variables define in .cpp
bool VolImage::readImages(std::string baseName){
        Metadata md = Utils::readDataFile(baseName);
        std::string baseName = md.baseName;
        int number_of_images = md.number_of_images;
        std::vector<unsigned char**> slices;
        for (int i = 0; i < number_of_images; i++)
                slices.push_back(readSlice(md,int(i)));
        return slices;
}

unsigned char** Utils::readSlice(Metadata h, int index){
        std::string baseName = h.baseName;
        int width = h.width;
        int height = h.height;
        // std::cout << "w: "<<width << '\n';
        // std::cout << "h: "<<height << '\n';
        std::string filepath = "assets/"+baseName+std::to_string(index)+".raw";
        std::ifstream raw_image(filepath,std::ios::in|std::ios::binary);
        if(!raw_image) throw std::runtime_error("Could not open file: "+ filepath);
        //Make a pointer to a pointer that points to a char
        unsigned char** pixel_rows;
        //Assign a pointer to the first element of the array(which is a pointer)
        // to the image**
        pixel_rows = new unsigned char* [height];
        char* buffer = new char[width+1];
        buffer[width] = '\0';
        int c = 0;
        for (int i = 0; i < height; i++) {
                raw_image.clear();                        //clear the buffer
                raw_image.seekg(i*(width), std::ios::beg); //reset the reading position to beginning
                raw_image.read(buffer,width);
                buffer[width] = '\0';
                unsigned char* convert_var = reinterpret_cast<unsigned char*>(buffer);
                *(convert_var+width) = '\0';
                *(pixel_rows+i) = convert_var;
                c++;
                buffer = new char[width+1];
                buffer[width] = '\0';
        }
        return pixel_rows;
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
