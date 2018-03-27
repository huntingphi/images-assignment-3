#include "../include/catch.hpp"
#include "../include/utils.h"
#include <string>
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <algorithm>


TEST_CASE("Test readDataFile"){
        Metadata expected("MRI",429, 303, 123);
        Metadata result = Utils::readDataFile("MRI");
        REQUIRE(expected.baseName == result.baseName);
        REQUIRE(expected.width == result.width);
        REQUIRE(expected.height == result.height);
        REQUIRE(expected.number_of_images == result.number_of_images);

}

TEST_CASE("Test readSlice"){
        std::ifstream expected_input( "/home/minad/Documents/CSC3022H/Assignments/Assignment 2/pointers and memory/assets/MRI0.raw", std::ios::binary );
        Metadata h("test",6,4,1);
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
        unsigned char** slice = new unsigned char* [height];
        slice = Utils::readSlice(h,0);
        bool flag = true;
        for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                        if(slice[i][j]!=expected[i][j]) flag = false;
                }
        }
        REQUIRE(flag);
}

TEST_CASE("Test writeSliceToFile"){
        std::ifstream expected_input( "/home/minad/Documents/CSC3022H/Assignments/Assignment 2/pointers and memory/assets/MRI0.raw",std::ios::in| std::ios::binary );
        // copies all expected data into buffer
        std::vector<char> expected_buffer((std::istreambuf_iterator<char>(expected_input)),(std::istreambuf_iterator<char>()));
        Metadata h("MRI",429,303,123);
        Utils::writeSliceToFile(Utils::readSlice(h,0),h,0);
        std::ifstream resulting_input( "/home/minad/Documents/CSC3022H/Assignments/Assignment 2/pointers and memory/assets_copy/MRI0copy.raw", std::ios::binary );
        // copies all resulting data into buffer
        std::vector<char> resulting_buffer((std::istreambuf_iterator<char>(resulting_input)),(std::istreambuf_iterator<char>()));
        REQUIRE(std::equal(expected_buffer.begin(), expected_buffer.end(), resulting_buffer.begin()));
}

TEST_CASE("Test readRawFiles"){
        Metadata h("MRI",429,303,123);
        int height = h.height;
        int width = h.width;
        std::vector<unsigned char**> raws = Utils::readRawFiles(h);
        unsigned char** slice = new unsigned char* [height];
        bool flag = true;
        for (int img_index = 0; img_index < h.number_of_images; img_index++) {
                slice = Utils::readSlice(h,img_index); //read slice for current index
                // bool flag = true;
                for (int i = 0; i < height; i++) {
                        for (int j = 0; j < width; j++) {
                                //if ever a char in one array doesnt correspond with the char in another then set flag false
                                if(slice[i][j]!=raws[img_index][i][j]) flag = false;
                        }
                }
                // REQUIRE(flag);


        }
        REQUIRE(flag);
}

TEST_CASE("Test VectorDifference"){
        Metadata h("MRI",429,303,123);
        std::vector<unsigned char**> volume = Utils::readRawFiles(h);
        Utils::writeSliceToFile(Utils::VectorDifference(h,volume,5,27),h,1);
        REQUIRE(1==1);
}

TEST_CASE("Test extractAcrossSlices"){
        Metadata h("MRI",429,303,123);
        Metadata o("MRI_ACROSS",429,123,1);
        std::vector<unsigned char**> volume = Utils::readRawFiles(h);
        // std::cout << (float)volume[0][0][0] << '\n';
        Utils::writeSliceToFile(Utils::extractAcrossSlices(h, volume, 0),o,0);
        REQUIRE(1==1);

}
