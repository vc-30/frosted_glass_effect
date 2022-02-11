/*
*		Code to generated frosted glass effect
*/
#include <stdio.h>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <math.h>

#include "image.hpp"
#include "utils/read_write.hpp"
#include "utils/image_operations.hpp"

using namespace std;

int main(int argc, char *argv[])

{
	FILE *file;
	
	// Check for params
	if (argc < 6){
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name input_image.raw output_image.raw [Width = 256] [Height = 256] [BytesPerPixel = 1] [filter_size = 3]" << endl;
		return 0;
	}
	
	string output_name = argv[2];
	int width = atoi(argv[3]);
	int height = atoi(argv[4]);
	int BytesPerPixel = atoi(argv[5]);
	int filter_size = atoi(argv[6]);
	
	dip::Image* src_image = new dip::Image(height, width, BytesPerPixel);

	// Read image (filename specified by first argument) into image data matrix
	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(src_image->data, sizeof(unsigned char), height*width*BytesPerPixel, file);
	fclose(file);

	//Add boundary reflection padding
	dip::Image* image_with_padding = new dip::Image(src_image->height+2, src_image->width+2, src_image->bpp);
  dip::image_proc::addReflectionPadding(*src_image, *image_with_padding);

	//Output container
	dip::Image* output_image = new dip::Image(height, width, BytesPerPixel);

	//Apply frosted glass effect
	dip::image_proc::frosted_glass_effect(*image_with_padding, *output_image, filter_size);
	dip::writeImage(*output_image, output_name);

	return 0;
}
