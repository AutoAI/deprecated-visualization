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
	uint8_t *next();
	bool hasNext();
	int numFrames();
	int bufferSize();

private:
	uint8_t *frame_buffer;
	std::ifstream is;
	int frame_number;
	int num_frames;
	int num_pixels;
	int buffer_size;
};

#endif    // _FRAME_BUFFER_H

