#include "../include/Header.h"
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
        for (int i = 0; i < number_of_images; i++) {
                // slices.push_back(readSlice(h,int(i)));
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



unsigned char** Utils::readSlice(Header h, int index){
        std::string baseName = h.baseName;
        int width = h.width;
        int height = h.height;

        std::string filepath = "../assets/"+baseName+std::to_string(index)+".data";
        std::ifstream raw_image(filepath,std::ios::binary);
        //Make a pointer to a pointer that points to a char
        unsigned char** pixel_rows;
        //Assign a pointer to the first element of the array(which is a pointer)
        // to the image**
        pixel_rows = new unsigned char* [height];
        char buffer[width]; //*height];
        // raw_image.read(buffer, width*height);
        int c = 0;
        for (int i = 0; i < height; i++) {
                pixel_rows[i] = new unsigned char[width];
                // std::cout << std::ios_base::cur << '\n';
                raw_image.clear();             //clear the buffer
                raw_image.seekg(i*width, std::ios::beg); //reset the reading position to beginning
                raw_image.read(buffer,width);
                //copy(begin,end,destination)=> copies from begin index(inclusive) to end index(exclusive) to destination in a given array
                // std::copy(buffer[i*width],buffer[i*width+width],pixel_rows[i]);
                unsigned char* convert_var = reinterpret_cast<unsigned char*>(buffer);
                pixel_rows[i] = convert_var;
                c++;


                // ++i;
        }
        std::cout << c<<" reads successful" << '\n';

        return pixel_rows;
}

void Utils::writeSliceToFile(unsigned char** slice, Header h, int index){
        std::string baseName = h.baseName;
        int width = h.width;
        int height = h.height;
        // std::ofstream newfile("cries");
        std::string filepath = "assets_copy/"+baseName+std::to_string(index)+"copy.raw";
        std::ofstream raw_image(filepath,std::ios::binary);
        int c = 0;

        for (int i = 0; i < height; i++) {
                raw_image.write((char*)slice[i],width);
                c++;
        }
        std::cout << c<<" writes successful" << '\n';
        raw_image.close();


}
