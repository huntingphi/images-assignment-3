#include "../include/driver.h"

#include <iostream>

int main(int argc, char *argv[]) {
        Operations op = parse_args(argc,argv);
        switch (op) {
        case Operations::BUILD:
                std::cout << "Building image..." << '\n';

                break;
        case Operations::DIFF_MAP:
                std::cout << "Calculating difference map..." << '\n';

                break;
        case Operations::EXTRACT:
                std::cout << "Extracting..." << '\n';
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
        bool run_failed = false;
        if (argc<6) {
                if(argc==5) {
                        // -d i j output file name:  compute a difference map between images i and j, and write this out to file
                        std::string s = argv[2];
                        std::string s1 = argv[1];
                        std::string s2 = argv[3];

                        bool has_only_digits = (s.find_first_not_of( "0123456789" ) == -1);
                        bool has_only_digits_1 = (s2.find_first_not_of( "0123456789" ) == -1);

                        if(s1=="-d"&&has_only_digits==true&&has_only_digits_1==true) return Operations::DIFF_MAP;

                }else if(argc == 4) {
                        // -x i output file name:  extract and write the slice with number i and write this out to file.
                        std::string s = argv[2];
                        std::string s1 = argv[1];
                        bool has_only_digits = (s.find_first_not_of( "0123456789" ) == -1);
                        if(s1=="-x"&&has_only_digits==true) return Operations::EXTRACT;


                }else if(argc == 1) return Operations::BUILD;
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


void showUsage(){
        std::cerr << "Usage: " << "runner" << " -d i j output file name" << std::endl;
        std::cerr << "Usage: " << "runner" << " -x i output file name" << std::endl;
        std::cerr << "Usage: " << "runner" << "" << std::endl;
}
