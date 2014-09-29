#ifndef RENDER_H
#define RENDER_H

#include <png.h>

typedef struct PNG {
  int width;
  int height;
  int depth;
  png_bytep color;
  png_structp pngp;
  png_byte color_type;
  png_infop infop;
  png_byte **data;
} PNG;

int put_pixel(PNG *png, size_t x, size_t y, uint32_t hex);
void write_png(PNG *png, char *fname);
PNG *create_png(int width, int height);

#endif
