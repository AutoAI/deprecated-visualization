// frame_buffer.h

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