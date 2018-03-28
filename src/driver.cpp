#include "../include/driver.h"
#include <iostream>


int main(int argc, char *argv[]) {
        Operations op = parse_args(argc,argv);
        switch (op) {
        case Operations::BUILD:
                std::cout << "Building image..." << '\n';
                build();

                break;
        case Operations::DIFF_MAP:
                std::cout << "Calculating difference map..." << '\n';
                diffmap();


                break;
        case Operations::EXTRACT:
                std::cout << "Extracting..." << '\n';
                extract();

                break;
        case Operations::EXTRACT_ACROSS_SLICES:
                std::cout << "Extracting across all slices..." << '\n';
                extract();

                break;
        case Operations::FAIL:
                showUsage();
                break;
        }
        return 0;
}


int mockMethod(){
        // Method to test that the test framework works;

        return 1;
}

Operations parse_args(int argc, char* argv[])
{
        // bool run_failed = false;
        if (argc<7) {
                baseName = argv[1];
                if(argc==6) {
                        // -d i j output file name:  compute a difference map between images i and j, and write this out to file
                        std::string s = argv[3];
                        std::string s1 = argv[2];
                        std::string s2 = argv[4];

                        bool has_only_digits = (s.find_first_not_of( "0123456789") ==-1);
                        bool has_only_digits_1 = (s2.find_first_not_of( "0123456789" ) ==-1);

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
                        bool has_only_digits = (s.find_first_not_of( "0123456789" )==-1);
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

void build(){
        image.readImages(baseName);
}

void extract(){
        build();
        image.extract(i,output_name);
}

void diffmap(){
        build();
        // std::cout << "i j output name"<<i<<j<<output_name << '\n';
        int* ip = &i;
        int* jp = &j;
        std::string* namep = &output_name;

        image.diffmap(*ip,*jp,*namep);

}

void extractAcrossSlices(){
        build();
        image.extractAcross(i,output_name);


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
