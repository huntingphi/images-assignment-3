#include "../include/catch.hpp"
#include "../include/utils.h"
#include "../include/Header.h"
#include <string>
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>

// TEST_CASE("Test slice writer","[multi-file:2]"){
//
//         std::ifstream expected_input( "/home/minad/Documents/CSC3022H/Assignments/Assignment 2/pointers and memory/assets/MRI0.raw", std::ios::binary );
//         // copies all expected data into buffer
//         std::vector<char> expected_buffer((std::istreambuf_iterator<char>(expected_input)),(std::istreambuf_iterator<char>()));
//
//
//         Header h("MRI",429,303,123);
//         Utils::writeSliceToFile(Utils::readSlice(h,0),h,0);
//
//         std::ifstream resulting_input( "/home/minad/Documents/CSC3022H/Assignments/Assignment 2/pointers and memory/assets_copy/MRI0copy.raw", std::ios::binary );
//         // copies all resulting data into buffer
//         std::vector<char> resulting_buffer((std::istreambuf_iterator<char>(resulting_input)),(std::istreambuf_iterator<char>()));
//
//
//         // REQUIRE(expected_buffer==resulting_buffer);
//         REQUIRE("Not testing yet: "  == "Writing out buffer to file");
//         // delete resulting_buffer;
//
// }
//

TEST_CASE("Test slice reader"){
        std::ifstream expected_input( "/home/minad/Documents/CSC3022H/Assignments/Assignment 2/pointers and memory/assets/MRI0.raw", std::ios::binary );
        // copies all expected data into buffer
        // std::vector<char> expected_buffer((std::istreambuf_iterator<char>(expected_input)),(std::istreambuf_iterator<char>()));
        Header h("line",4,6,1);
        int height = h.height;
        int width = h.width;

        unsigned char line0[]="line 0";
        unsigned char line1[]="line 1";
        unsigned char line2[]="line 2";
        unsigned char line3[]="line 3";


        unsigned char** expected = new unsigned char* [4];
        expected[0] =line0;
        expected[1] =line1;
        expected[2] =line2;
        expected[3] =line3;


        // unsigned char buffer[height*width]; //*height];

        unsigned char** slice = new unsigned char* [height];
        slice = Utils::readSlice(h,0);

        std::cout << "TEST VALUES" << '\n';

        for (int i = 0; i < height; i++) {
                std::cout<<"row: "<<*(slice+i);
                std::cout << '\n';

                /* code */
        }

        REQUIRE(1!=1);


}
