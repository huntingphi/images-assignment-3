#include <string>

struct Header {
        std::string baseName;
        int width;
        int height;
        int number_of_images;

        Header(std::string name, int h, int w, int no_imgs) : baseName(name), height(h), width(w), number_of_images(no_imgs){
        }

};
