// frame_buffer.cc

#include "bitmap_loader.h"

#include "frame_buffer.h"
#include "bitmap_image.hpp"

#include <iostream>

BitmapLoader::BitmapLoader(std::string file_name, int x_resolution, int y_resolution, char num_channels) {
	// calculate some things so that this class works like the FrameBuffer class
	num_pixels = x_resolution * y_resolution;
	buffer_size = sizeof(uint8_t) * num_pixels * num_channels;
	frame_buffer = new uint8_t[buffer_size];

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
			frame_buffer[i] = r / 3 + b / 3 + g / 3;
		}
	} else
	// color
	if(num_channels == 3) {
		for(int i = 0; i < num_pixels; i++) {
			image -> get_pixel(i % x_resolution, i / x_resolution, r, g, b);
			frame_buffer[i] = r;
			frame_buffer[i + num_pixels] = g;
			frame_buffer[i + num_pixels + num_pixels] = b;
		}
	} else
	// color + alpha
	if(num_channels == 4) {
		for(int i = 0; i < num_pixels; i++) {
			image -> get_pixel(i % x_resolution, i / x_resolution, r, g, b);
			frame_buffer[i] = r;
			frame_buffer[i + num_pixels] = g;
			frame_buffer[i + num_pixels + num_pixels] = b;
			frame_buffer[i + 3 * num_pixels] = 255;
		}
	} else {
		std::cout << "Not sure how to create buffer for " << num_channels << " channels... <bitmap_loader.cpp>" << std::endl;
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