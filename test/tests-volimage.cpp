#include "../include/catch.hpp"
#include "../include/volimage.h"


TEST_CASE("Test the test runner","[multi-file:2]"){
  VolImage v;
  REQUIRE(v.mockMethod()==1);
}
