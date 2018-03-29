#include "../include/catch.hpp"
#include "../include/volimage.h"
// #include "../include/driver.h"
#include <string>
#include <iostream>
#include <fstream>


TEST_CASE("Test readDataFile"){
        VolImage image;
        Metadata expected("MRI",429, 303, 123);
        Metadata result = image.readDataFile("MRI");
        REQUIRE(expected.baseName == result.baseName);
        REQUIRE(expected.width == result.width);
        REQUIRE(expected.height == result.height);
        REQUIRE(expected.number_of_images == result.number_of_images);

}

TEST_CASE("Test readSlice"){
        VolImage image;
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
        slice = image.readSlice(h,0);
        bool flag = true;
        for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                        if(slice[i][j]!=expected[i][j]) flag = false;
                }
        }
        REQUIRE(flag);
}

TEST_CASE("Test writeSliceToFile"){
        VolImage image;
        std::ifstream expected_input( "assets/MRI0.raw",std::ios::in| std::ios::binary );
        // copies all expected data into buffer
        std::vector<char> expected_buffer((std::istreambuf_iterator<char>(expected_input)),(std::istreambuf_iterator<char>()));
        Metadata h("MRI",429,303,123);
        image.readRawFiles("MRI");
        std::vector<unsigned char**> raws = image.getSlices();
        image.writeSliceToFile(image.readSlice(h,0),h,"SliceTest");
        std::ifstream resulting_input( "output_raws/SliceTest.raw", std::ios::binary );
        // copies all resulting data into buffer
        std::vector<char> resulting_buffer((std::istreambuf_iterator<char>(resulting_input)),(std::istreambuf_iterator<char>()));
        REQUIRE(std::equal(expected_buffer.begin(), expected_buffer.end(), resulting_buffer.begin()));
}

TEST_CASE("Test readRawFiles"){
        VolImage image;
        Metadata h("MRI",429,303,123);
        int height = h.height;
        int width = h.width;
        image.readRawFiles("MRI");
        std::vector<unsigned char**> raws = image.getSlices();

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
        VolImage image;
        Metadata h("MRI",429,303,123);
        image.readRawFiles("MRI");
        Metadata o("5_27_Diffmap",429,303,123);

        std::vector<unsigned char**> volume = image.getSlices();
        image.writeSliceToFile(image.VectorDifference(h,volume,5,27),h,"5_27_DiffmapTest");
        std::ifstream expected_input( "assets/5_27_Diffmap.raw",std::ios::in| std::ios::binary );
        // copies all expected data into buffer
        std::vector<char> expected_buffer((std::istreambuf_iterator<char>(expected_input)),(std::istreambuf_iterator<char>()));
        std::ifstream resulting_input( "output_raws/5_27_DiffmapTest.raw", std::ios::binary );
        // copies all resulting data into buffer
        std::vector<char> resulting_buffer((std::istreambuf_iterator<char>(resulting_input)),(std::istreambuf_iterator<char>()));
        REQUIRE(std::equal(expected_buffer.begin(), expected_buffer.end(), resulting_buffer.begin()));
        REQUIRE(1==1);
}

TEST_CASE("Test extractAcrossSlices"){
        VolImage image;
        Metadata h("MRI",429,303,123);
        Metadata o("MRI_ACROSS",429,123,1);
        std::vector<unsigned char**> volume = Utils::readRawFiles(h);
        // std::cout << (float)volume[0][0][0] << '\n';
        image.writeSliceToFile(image.extractAcrossSlices(h, volume, 0),o,0);
        REQUIRE(1==1);

}


TEST_CASE("CHANGE FUNCTION NAMES AND PARAMETERS TO MATCH CLASS SPEC"){
        REQUIRE(1==0);
}
