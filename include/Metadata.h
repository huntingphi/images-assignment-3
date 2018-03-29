#ifndef METADATA
  #define  METADATA
#include <string>
struct Metadata {
        std::string baseName;
        int width;
        int height;
        int number_of_images;

        Metadata(std::string name, int w, int h, int no_imgs) : baseName(name), width(w), height(h),number_of_images(no_imgs){
        }

};
#endif
