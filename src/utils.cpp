#include "../include/Header.h"
#include "../include/utils.h"
#include <vector>
#include <iostream>
#include <fstream>


using namespace Utils;

Header readDataFile(std::string baseName){


}

std::vector<unsigned char**> Utils::readRawFiles(Header h){
        std::string baseName = h.baseName;
        int number_of_images = h.number_of_images;
        std::vector<unsigned char**> slices;
        for (int i = 0; i < number_of_images; i++)
                slices.push_back(readSlice(h,int(i)));
        return slices;
}



unsigned char** Utils::readSlice(Header h, int index){
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

void Utils::writeSliceToFile(unsigned char** slice, Header h, int index){
        std::string baseName = h.baseName;
        int width = h.width;
        int height = h.height;
        std::cout << "w: "<<width << '\n';
        // std::cout << "h: "<<height << '\n';
        std::string filepath = "assets_copy/"+baseName+std::to_string(index)+"copy.raw";
        std::ofstream raw_image(filepath,std::ios::binary);
        if(!raw_image) throw std::runtime_error("Could not open file: "+ filepath);
        int c = 0;
        for (int i = 0; i < height; i++) {
                raw_image.write((char*)slice[i],width);
                c++;
        }
        std::cout << c<<" writes successful" << '\n';
        raw_image.close();
}

unsigned char** Utils::VectorDifference(Header h,std::vector<unsigned char**> volume,int i, int j){
        int height = h.height;
        int width = h.width;
        unsigned char** diffmap = new unsigned char* [height];
        for (int r = 0; r < height; r++) {
                diffmap[r] = new unsigned char[width];
                for (int c = 0; c < width; c++) {
                        //if ever a char in one array doesnt correspond with the char in another then set flag false
                        diffmap[r][c]= abs((float)volume[i][r][c]-(float)volume[j][r][c]);
                }
        }
        return diffmap;
}

unsigned char** Utils::extractAcrossSlices(Header h,std::vector<unsigned char**> volume,int row){
        int width = h.width;
        std::cout << width << '\n';
        int num_imgs = h.number_of_images;
        unsigned char** accross_slices = new unsigned char* [num_imgs];
        for (int img_index = 0; img_index < num_imgs; img_index++) {
                accross_slices[img_index] = new unsigned char[width];
                // accross_slices[width] = '\0';
                for (int c = 0; c < width; c++) {

                        //if ever a char in one array doesnt correspond with the char in another then set flag false
                        // std::cout << "Accessing [img_index][row][column]: "<<img_index<<" "<<row<<" "<<c << '\n';
                        accross_slices[img_index][c]= volume[img_index][row][c];
                }
        }
        return accross_slices;

}
