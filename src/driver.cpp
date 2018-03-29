#ifndef HEADERFILE
  #define HEADERFILE
  #include "../include/driver.h"
#endif
#include <iostream>


int main(int argc, char *argv[]) {

        Utils::Operations op = Utils::parse_args(argc,argv);
        switch (op) {
        case Utils::Operations::BUILD:
                std::cout << "Building image..." << '\n';
                // build(argv);

                break;
        case Utils::Operations::DIFF_MAP:
                std::cout << "Calculating difference map..." << '\n';
                diffmap(argv);


                break;
        case Utils::Operations::EXTRACT:
                std::cout << "Extracting..." << '\n';
                extract(argv);

                break;
        case Utils::Operations::EXTRACT_ACROSS_SLICES:
                std::cout << "Extracting across all slices..." << '\n';
                extract(argv);

                break;
        case Utils::Operations::FAIL:
                showUsage();
                break;
        }
        return 0;
}


int mockMethod(){
        // Method to test that the test framework works;

        return 1;
}



void build(char* argv[]){
        std::string baseName = argv[1];
        // image = new VolImage();
        // image.readImages(baseName);

        // std::cout << "lol" << '\n';

}

void extract(char* argv[]){
        std::string baseName = argv[1];

}

void diffmap(char* argv[]){
        std::string baseName = argv[1];

}

void extractAcrossSlices(char* argv[]){
        std::string baseName = argv[1];

}



void showUsage(){
        std::cerr << "Usage: " << "runner" << " <imageBase> -d i j output file name" << std::endl;
        std::cerr << "Usage: " << "runner" << " <imageBase> -x i output file name" << std::endl;
        std::cerr << "Usage: " << "runner" << " <imageBase> -g i output file name" << std::endl;

        std::cerr << "Usage: " << "runner" << " <imageBase>" << std::endl;
}

void showOperationInfo(int num_imgs,int num_bytes){
        std::cout << "Number of images: " <<num_imgs<< '\n';
        std::cout << "Number of bytes required: " <<num_bytes<< '\n';
}
