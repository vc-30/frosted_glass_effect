/*
* Basic image container class (needs modification to make it feature rich)
*/
#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <math.h>
#include <cstdlib>

namespace dip {
    class Image {
        public:
            // Image();

            Image(int height, int width, int bpp)
            {
                this->height = height;
                this->width = width;
                this->bpp = bpp;
                data = (unsigned char*) calloc(height*width*bpp, sizeof(unsigned char)); //to find holes
            }

            ~Image()
            {
                free(data);
                data = nullptr; //prevent dangling pointer
            }

            int height;
            int width;
            int bpp;
            unsigned char* data;
    };
}
#endif //