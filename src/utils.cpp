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
        // std::cout << "width: "<<width << '\n';
        // std::cout << "height: "<<height << '\n';

        std::string filepath = "assets/"+baseName+std::to_string(index)+".raw";
        std::ifstream raw_image(filepath,std::ios::in|std::ios::binary);

        if(!raw_image) { //Show if file found
                // std::cout << filepath<<" FILE DNE!" << '\n';
                // return false;
                throw std::runtime_error("Could not open file");
        }
        //Make a pointer to a pointer that points to a char
        unsigned char** pixel_rows;
        //Assign a pointer to the first element of the array(which is a pointer)
        // to the image**
        pixel_rows = new unsigned char* [height];
        char* buffer = new char[width+1]; //*height];
        // raw_image.read(buffer, width*height);
        int c = 0;
        for (int i = 0; i < height; i++) {
                if(i!=0) std::cout << *(pixel_rows+(i-1)) << '\n';

                // *(pixel_rows+i) = new unsigned char[width+1];
                // std::cout << std::ios_base::cur << '\n';
                raw_image.clear();                        //clear the buffer
                raw_image.seekg(i*(width), std::ios::beg); //reset the reading position to beginning
                // std::cout << raw_image.tellg() << '\n';
                raw_image.read(buffer,width);
                // printf("Buffer: %s",buffer);
                // std::cout << '\n';
                buffer[width] = '\0';

                //copy(begin,end,destination)=> copies from begin index(inclusive) to end index(exclusive) to destination in a given array
                // std::copy(buffer[i*width],buffer[i*width+width],pixel_rows[i]);
                // std::cout << *(buffer+(width-1)) << '\n';
                unsigned char* convert_var = reinterpret_cast<unsigned char*>(buffer);
                *(convert_var+width) = '\0';
                // printf("convert_var: %s",convert_var);
                // std::cout << '\n';


                *(pixel_rows+i) = convert_var;

                // delete pixel_rows[i];
                c++;
                buffer = new char[width+1];

                // ++i;
        }
        // std::cout << *(pixel_rows+(1)) << '\n';

        std::cout << height << '\n';
        for (int i = 0; i < height; i++) {
                std::cout<<"row: "<<*(pixel_rows+i);
                std::cout << '\n';

                /* code */
        }

        // std::cout << c<<" reads successful" << '\n';

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
