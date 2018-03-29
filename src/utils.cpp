// #include "../include/Metadata.h"
// #include "../include/volimage.h"
#ifndef HEADERFILE
  #define HEADERFILE
  #include "../include/utils.h"
#endif
#include <vector>
#include <iostream>
#include <fstream>


using namespace Utils;

Operations Utils::parse_args(int argc, char* argv[]){
        int i;
        int j;
        std::string output_name;
        bool run_failed = false;
        if (argc<7) {
                if(argc==6) {
                        // -d i j output file name:  compute a difference map between images i and j, and write this out to file
                        std::string s = argv[3];
                        std::string s1 = argv[2];
                        std::string s2 = argv[4];

                        bool has_only_digits = (s.find_first_not_of( "0123456789" ) == -1);
                        bool has_only_digits_1 = (s2.find_first_not_of( "0123456789" ) == -1);

                        if(s1=="-d"&&has_only_digits==true&&has_only_digits_1==true) {
                                i = atoi(argv[3]);
                                j = atoi(argv[4]);
                                output_name = argv[5];

                                return Operations::DIFF_MAP;
                        }

                }else if(argc == 5) {
                        // -x i output file name:  extract and write the slice with number i and write this out to file.
                        std::string s = argv[3];
                        std::string s1 = argv[2];
                        bool has_only_digits = (s.find_first_not_of( "0123456789" ) == -1);
                        if(has_only_digits==true) {
                                if(s1=="-x") return Operations::EXTRACT;
                                if(s1=="-g") return Operations::EXTRACT_ACROSS_SLICES;
                                i = atoi(argv[3]);
                                output_name = argv[4];
                        }


                }else if(argc == 2) return Operations::BUILD;
                // build the internal representation
                // and then exit after ensuring memory is correctly cleaned up,
                // and print the following to the console:
                // Number of images:  (int)
                // Number of bytes required:  (int)

        }


        return Operations::FAIL;

        // if(run_failed == true){
        //   showUsage();
        //   return 1;
        // }else{
        //   return 0;
        // }




}

Metadata Utils::readDataFile(std::string baseName){
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

std::vector<unsigned char**> Utils::readRawFiles(Metadata h){
        std::string baseName = h.baseName;
        int number_of_images = h.number_of_images;
        std::vector<unsigned char**> slices;
        for (int i = 0; i < number_of_images; i++)
                slices.push_back(readSlice(h,int(i)));
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

void Utils::writeSliceToFile(unsigned char** slice, Metadata h, int index){
        std::string baseName = h.baseName;
        int width = h.width;
        int height = h.height;
        std::cout << "w: "<<width << '\n';
        // std::cout << "h: "<<height << '\n';
        std::string filepath = "output_raws/"+baseName+std::to_string(index)+"copy.raw";
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



unsigned char** Utils::VectorDifference(Metadata h,std::vector<unsigned char**> volume,int i, int j){
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

unsigned char** Utils::extractAcrossSlices(Metadata h,std::vector<unsigned char**> volume,int row){
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
