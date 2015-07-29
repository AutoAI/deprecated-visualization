// frame_buffer.cc

#include "frame_buffer.h"

#include <iostream>

FrameBuffer::FrameBuffer(std::string file_name, int x_resolution, int y_resolution) {
	// dynamically allocate the frame buffer
	num_pixels = x_resolution * y_resolution;
	buffer_size = sizeof(uint32_t) * num_pixels;
	frame_buffer_32 = new uint32_t[num_pixels];
	frame_buffer_8 = NULL;
	if(!frame_buffer_32) {
		std::cout << "Failed to allocate buffer" << std::endl;
		return;
	}

	// open the file
    is.open(file_name.c_str(), is.binary);
    if(!is.is_open()) {
    	std::cout << "Failed to open the file." << std::endl;
    	return;
    }

    // find the number of frames
	is.seekg(0, is.end);
	int file_size = is.tellg();
	is.seekg (0, is.beg);
	if(file_size == 0) {
		std::cout << "Warning: file size is 0" << std::endl;
	}
	num_frames = file_size / buffer_size;

	frame_number = 0;
}

FrameBuffer::FrameBuffer(std::string file_name, int x_resolution, int y_resolution, char num_channels) {
	// dynamically allocate the frame buffer
	num_pixels = x_resolution * y_resolution;
	buffer_size = sizeof(uint8_t) * num_pixels * num_channels;
	frame_buffer_8 = new uint8_t[num_pixels * num_channels];
	frame_buffer_32 = NULL;
	if(!frame_buffer_8) {
		std::cout << "Failed to allocate buffer" << std::endl;
		return;
	}

	// open the file
    is.open(file_name.c_str(), is.binary);
    if(!is.is_open()) {
    	std::cout << "Failed to open the file." << std::endl;
    	return;
    }

    // find the number of frames
	is.seekg(0, is.end);
	int file_size = is.tellg();
	is.seekg (0, is.beg);
	if(file_size == 0) {
		std::cout << "Warning: file size is 0" << std::endl;
	}
	num_frames = file_size / buffer_size;

	frame_number = 0;
}

uint32_t *FrameBuffer::next32() {
	// load each frame into the buffer
	is.read(reinterpret_cast<char*>(frame_buffer_32), buffer_size);
	uint32_t temp;

	// reverse order of bytes
	for(int i = 0; i < num_pixels; i++) {
		temp = frame_buffer_32[i];
		frame_buffer_32[i] = (temp >> 24) | ((temp & 0x00FF0000) >> 8) | ((temp & 0x0000FF00) << 8) | ((temp & 0x000000FF) << 24);
	}

	frame_number++;
	if(frame_buffer_32 == NULL) {
		std::cout << "BitmapLoader::next() returned NULL! <frame_buffer.cc>" << std::endl;
	}
	return frame_buffer_32;
}

uint8_t *FrameBuffer::next8() {
	// load each frame into the buffer
	is.read(reinterpret_cast<char*>(frame_buffer_8), buffer_size);

	frame_number++;
	if(frame_buffer_8 == NULL) {
		std::cout << "BitmapLoader::next() returned NULL! <frame_buffer.cc>" << std::endl;
	}
	return frame_buffer_8;
}

bool FrameBuffer::hasNext() {
	return frame_number != num_frames;
}

int FrameBuffer::numFrames() {
	return num_frames;
}

int FrameBuffer::bufferSize() {
	return buffer_size;
}