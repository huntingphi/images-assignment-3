#include <string>

struct Header {
        std::string baseName;
        int width;
        int height;
        int number_of_images;

        Header(std::string name, int w, int h, int no_imgs) : baseName(name), width(w), height(h), number_of_images(no_imgs){
        }

};
