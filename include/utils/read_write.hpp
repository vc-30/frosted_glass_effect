#ifndef READ_WRITE_HPP
#define READ_WRITE_HPP

#include <iostream>
#include "image.hpp"

using namespace std;

namespace dip {
    void PrintImageData(Image& image)
    {
        for(int row=0; row<image.height; row++)
        {
            for(int col=0;col<image.width; col++)
            {
                for(int ch=0; ch<image.bpp; ch++)
                {
                    std::cout << (int)*(image.data+row*image.width*image.bpp+col*image.bpp+ch) << " ";
                }
            }
            cout << endl;
        }
    }

    void writeImage(Image& image, string file_name)
    {
        FILE *file;
        std::cout<<"Writing"<<std::endl;
        if (!(file=fopen((file_name+".raw").c_str(),"wb"))) {
            cout << "Cannot open file: " << file_name << endl;
            exit(1);
        }
        fwrite(image.data, sizeof(unsigned char), image.height*image.width*image.bpp, file);
        fclose(file);
    }

}

#endif //READ_WRITE_HPP