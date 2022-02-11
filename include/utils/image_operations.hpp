#ifndef IMAGE_OPERATIONS_HPP
#define IMAGE_OPERATIONS_HPP

#include <iostream>
#include <vector>
#include <stdlib.h>
#include "image.hpp"


namespace dip
{
    namespace image_proc
    {
        inline unsigned char saturate_cast(double val)
        {
            val = round(val);
            return (val <= 0 ? 0 : (val >= 0xFF ? 0xFF : val ));
        }

        void frosted_glass_effect(const Image& src_image,Image& output_image,int filter_size)
        {
            //center pixel coordinates
            int cpx_x = filter_size/2;
            int cpx_y = filter_size/2;
            int bpp = src_image.bpp;
            for(int row=0; row < (output_image.height); row++)
            {
                for(int col=0; col < (output_image.width); col++)
                {
                    int r = rand() % filter_size;
                    int c = rand() % filter_size;
                    
                    if((r+row)>=src_image.height)
                    {
                        r = 0;
                    }
                    if((c+col)>=src_image.width)
                    {
                        c = 0;
                    }

                    for(int ch=0; ch < src_image.bpp; ch++)
                    {
                        output_image.data[row*output_image.width*bpp+ col*bpp+ch] = src_image.data[(row+r)*src_image.width*bpp+(col+c)*bpp+ch];
                    }
                }
            }
        }

        void addReflectionPadding(Image &src_image, Image &dest_image)
        {
            int bpp = src_image.bpp;
            //filling the center with input image data
            for(int row=0; row < src_image.height; row++)
            {
                for(int col=0; col < src_image.width; col++)
                {
                    for(int ch=0; ch < bpp; ch++)
                    {
                        dest_image.data[(row+1)*dest_image.width*bpp+col*bpp + 1*bpp + ch] = \
                        src_image.data[row*src_image.width*src_image.bpp+col*src_image.bpp + ch];
                    }
                }
            }

            //top and bottom padding
            for(int col=0; col < src_image.width; col++)
            {
                for(int ch=0; ch < bpp; ch++)
                {
                    dest_image.data[col*bpp+1*bpp+ch] = src_image.data[src_image.width*bpp+col*bpp+ch];
                    dest_image.data[dest_image.width*(dest_image.height-1)*bpp+1*bpp+col*bpp + ch] =\
                    src_image.data[src_image.width*(src_image.height-2)*bpp+col*bpp+ch];
                }
            }

            //left and right padding
            for(int row=0; row < src_image.height; row++)
            {
                for(int ch=0; ch < bpp; ch++)
                {
                    dest_image.data[(row+1)*dest_image.width*bpp] = src_image.data[row*src_image.width*bpp+1*bpp+ch];
                    dest_image.data[(row+2)*dest_image.width*bpp-1*bpp] = src_image.data[(row+1)*src_image.width*bpp-2*bpp];
                }
            }

            for(int ch=0; ch < bpp; ch++)
            {
                dest_image.data[ch] = src_image.data[src_image.width*bpp+1*bpp+ch]; //top left
                dest_image.data[dest_image.width*bpp-1*bpp] = src_image.data[2*src_image.width*bpp-2*bpp+ch]; //top right

                dest_image.data[dest_image.width*(dest_image.height-1)*bpp] = src_image.data[src_image.width*(src_image.height-2)*bpp+1*bpp]; //bottom left
                dest_image.data[dest_image.width*dest_image.height*bpp-1*bpp] = src_image.data[src_image.width*(src_image.height-1)*bpp-2*bpp];
            }
        }


        void convolve2D(const Image& src_image, Image& output_image, std::vector<std::vector<double>> kernel, int stride=1)
        {
            const int cy = kernel.size()/2;
            const int cx = kernel[0].size()/2;
            
            for(int row=0; row<src_image.height; row+=stride)
            {
                for(int col=0; col<src_image.width; col+=stride)
                {
                    double temp[src_image.bpp]={0.0};
                    for(int k_row=0; k_row < kernel.size(); k_row++)
                    {
                        for(int k_col=0; k_col < kernel[0].size(); k_col++)
                        {
                            int x = col - cx + k_col;
                            int y = row - cy + k_row;
                            if(x>=0 && x < src_image.width && y>=0 && y < src_image.height)
                            {
                                for(int ch=0; ch < src_image.bpp; ch++)
                                {
                                    temp[ch] += src_image.data[y*src_image.width*src_image.bpp + x*src_image.bpp + ch] * \
                                                kernel[k_row][k_col];
                                }
                            }
                        }
                    }
                    int x = col - cx;
                    int y = row - cy;
                    if(x>=0 && x < src_image.width && y>=0 && y < src_image.height)
                    {
                        for(int ch=0; ch<output_image.bpp; ch++)
                        {
                            output_image.data[y*output_image.width*output_image.bpp + x*output_image.bpp + ch] = saturate_cast(temp[ch]);
                        }
                    }
                }
            }
        }

        void convolve(const Image& src_image, Image& output_image, std::vector<std::vector<double>> kernel,int padding=0,int stride=1)
        {
            convolve2D(src_image, output_image, kernel, stride);    
        }
    }
}

#endif //IMAGE_OPERATIONS_HPP