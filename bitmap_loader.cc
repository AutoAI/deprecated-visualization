// frame_buffer.cc

#include "bitmap_loader.h"

#include "frame_buffer.h"
#include "bitmap_image.hpp"

#include <iostream>

BitmapLoader::BitmapLoader(std::string file_name, int x_resolution, int y_resolution) {
	// calculate some things so that this class works like the FrameBuffer class
	num_pixels = x_resolution * y_resolution;
	buffer_size = sizeof(uint8_t) * num_pixels;
	frame_buffer = new uint8_t[buffer_size];

	// load the image
	bitmap_image *image = new bitmap_image(file_name);
	if(image == NULL) {
		std::cout << "Failed to allocate memory for image <bitmap_loader.cpp>" << std::endl;
	}
	unsigned char r, g, b;
	for(int i = 0; i < num_pixels; i++) {
		image -> get_pixel(i % x_resolution, i / x_resolution, r, g, b);
		frame_buffer[i] = r / 3 + b / 3 + g / 3;
	}

	num_frames = 1;
	frame_number = 0;
}

uint8_t *BitmapLoader::next() {
	if(frame_buffer == NULL) {
		std::cout << "BitmapLoader::next() returned NULL!" << std::endl;
	}
	return frame_buffer;
}

bool BitmapLoader::hasNext() {
	return frame_number != num_frames;
}

int BitmapLoader::numFrames() {
	return num_frames;
}

int BitmapLoader::bufferSize() {
	return buffer_size;
}