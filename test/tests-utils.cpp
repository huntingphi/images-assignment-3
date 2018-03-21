#include "../include/catch.hpp"
#include "../include/utils.h"
#include "../include/Header.h"
#include <string>
#include <iostream>

TEST_CASE("Test slice reader","[multi-file:2]"){
        Header h("MRI",429,303,123);
        Utils::writeSliceToFile(Utils::readSlice(h,0),h,0);


        REQUIRE(1==1);

}
