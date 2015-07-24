// frame_buffer.h

#if !defined(_FRAME_BUFFER_H)
#define _FRAME_BUFFER_H

#include <stdint.h>
#include <cstdlib>
#include <fstream>
#include <sstream>

class FrameBuffer {
public:
	FrameBuffer(std::string file_name, int x_resolution, int y_resolution);
	FrameBuffer(std::string file_name, int x_resolution, int y_resolution, char num_channels);
	uint8_t *next8();
	uint32_t *next32();
	bool hasNext();
	int numFrames();
	int bufferSize();

private:
	uint8_t *frame_buffer_8;
	uint32_t *frame_buffer_32;
	std::ifstream is;
	int frame_number;
	int num_frames;
	int num_pixels;
	int buffer_size;
};

#endif    // _FRAME_BUFFER_H