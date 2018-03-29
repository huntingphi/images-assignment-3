#include <string>
#ifndef VOLIMAGE
  #define VOLIMAGE
  #include "volimage.h"
#endif
int main(int argc, char* argv[]);
void showUsage();
int mockMethod();
void build(char* argv[]);
void diffmap(char* argv[]);
void extract(char* argv[]);

VolImage image;
std::string baseName;
int i;
int j;
std::string output_name;
