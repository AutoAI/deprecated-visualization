// bitmap_loader.h

#if !defined(_BITMAP_LOADER_H)
#define _BITMAP_LOADER_H

#include <stdint.h>
#include <cstdlib>
#include <fstream>
#include <sstream>

class BitmapLoader {
public:
  BitmapLoader(std::string file_name, int x_resolution, int y_resolution, char num_channels);
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

#endif      // _BITMAP_LOADER_H