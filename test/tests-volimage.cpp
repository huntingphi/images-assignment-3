#include "../include/catch.hpp"
#include "../include/volimage.h"
#include "../include/driver.h"
#include <string>
#include <iostream>

TEST_CASE("Test the test runner","[multi-file:2]"){
  VolImage v;
  REQUIRE(v.mockMethod()==1);
}

TEST_CASE("Test the program runner runner","[multi-file:1]"){

  int argc = 0;
  char* option1[1] = { "One"};//should pass
  char* option2[2] = { "One", "Two"};//should fail
  char* option3[3] = { "One", "Two","Three"};//should fail
  char* option4[4] = { "One", "-x","5","random_string"};//should pass
  char* option5[5] = { "One", "-d","5","j","random_string"};//should pass
  char* option6[6] = { "One", "-x","5","","random_string","random"};//should fail
  argc++;
  REQUIRE(parse_args(argc,option1)==Operations::BUILD);//should pass

  argc++;
  REQUIRE(parse_args(argc,option2)==Operations::FAIL);//should fail

  argc++;
  REQUIRE(parse_args(argc,option3)==Operations::FAIL);//should fail

  argc++;
  REQUIRE(parse_args(argc,option4)==Operations::EXTRACT);//should pass

  argc++;
  REQUIRE(parse_args(argc,option5)==Operations::DIFF_MAP);//should pass

  argc++;
  REQUIRE(parse_args(argc,option6)==Operations::FAIL);//should fail




}
