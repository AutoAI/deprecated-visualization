// frame_buffer.cc

#include "bitmap_loader.h"

#include "frame_buffer.h"
#include "bitmap_image.hpp"

#include <iostream>

BitmapLoader::BitmapLoader(std::string file_name, int x_resolution, int y_resolution) {
	// calculate some things so that this class works like the FrameBuffer class
	num_pixels = x_resolution * y_resolution;
	buffer_size = sizeof(uint32_t) * num_pixels;
	frame_buffer_32 = new uint32_t[num_pixels];
	frame_buffer_8 = NULL;

	// load the image
	bitmap_image *image = new bitmap_image(file_name);
	if(image == NULL) {
		std::cout << "Failed to allocate memory for image! <bitmap_loader.cpp>" << std::endl;
	}
	unsigned char r, g, b;
	for(int i = 0; i < num_pixels; i += 4) {
		image -> get_pixel(i % x_resolution, i / x_resolution, r, g, b);
		// load with red as most significant digits
		frame_buffer_32[i] = (r << 24) + (g << 16) + (b << 8) + 255;
	}

	num_frames = 1;
	frame_number = 0;
}

BitmapLoader::BitmapLoader(std::string file_name, int x_resolution, int y_resolution, char num_channels) {
	// calculate some things so that this class works like the FrameBuffer class
	num_pixels = x_resolution * y_resolution;
	buffer_size = sizeof(uint8_t) * num_pixels * num_channels;
	frame_buffer_8 = new uint8_t[num_pixels * num_channels];
	frame_buffer_32 = NULL;

	// load the image
	bitmap_image *image = new bitmap_image(file_name);
	if(image == NULL) {
		std::cout << "Failed to allocate memory for image! <bitmap_loader.cpp>" << std::endl;
	}
	unsigned char r, g, b;
	// black and white
	if(num_channels == 1) {
		for(int i = 0; i < num_pixels; i++) {
			image -> get_pixel(i % x_resolution, i / x_resolution, r, g, b);
			frame_buffer_8[i] = r / 3 + b / 3 + g / 3;
		}
	} else
	// color
	if(num_channels == 3) {
		for(int i = 0; i < num_pixels; i++) {
			image -> get_pixel(i % x_resolution, i / x_resolution, r, g, b);
			frame_buffer_8[i] = r;
			frame_buffer_8[i + num_pixels] = g;
			frame_buffer_8[i + num_pixels + num_pixels] = b;
		}
	} else
	// color + alpha
	if(num_channels == 4) {
		for(int i = 0; i < num_pixels; i++) {
			image -> get_pixel(i % x_resolution, i / x_resolution, r, g, b);
			frame_buffer_8[i] = r;
			frame_buffer_8[i + num_pixels] = g;
			frame_buffer_8[i + num_pixels + num_pixels] = b;
			frame_buffer_8[i + 3 * num_pixels] = 255;
		}
	} else {
		std::cout << "Not sure how to create buffer for " << num_channels << " channels... <bitmap_loader.cpp>" << std::endl;
	}

	num_frames = 1;
	frame_number = 0;
}

uint32_t *BitmapLoader::next32() {
	if(frame_buffer_32 == NULL) {
		std::cout << "BitmapLoader::next() returned NULL!" << std::endl;
	}
	return frame_buffer_32;
}

uint8_t *BitmapLoader::next8() {
	if(frame_buffer_8 == NULL) {
		std::cout << "BitmapLoader::next() returned NULL!" << std::endl;
	}
	return frame_buffer_8;
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