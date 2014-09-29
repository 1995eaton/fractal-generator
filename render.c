#include <stdlib.h>
#include <stdint.h>
#include "render.h"

int put_pixel(PNG *png, size_t x, size_t y, uint32_t hex) {
  if (x < 0 || y < 0 || x >= png->width || y >= png->height) {
    return -1;
  }
  uint8_t *rgb = (uint8_t*) &hex;
  png_bytep pixel = &(png->data[y][x*3]);
  pixel[0] = rgb[0];
  pixel[1] = rgb[1];
  pixel[2] = rgb[2];
  return 0;
}

void write_png(PNG *png, char *fname) {
  FILE *fp = fopen(fname, "wb");
  png->pngp = png_create_write_struct(PNG_LIBPNG_VER_STRING,
      NULL, NULL, NULL);
  png->infop = png_create_info_struct(png->pngp);
  png_init_io(png->pngp, fp);
  png_set_IHDR(png->pngp, png->infop, png->width, png->height,
      png->depth, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
      PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_DEFAULT);
  png_write_info(png->pngp, png->infop);
  png_write_image(png->pngp, png->data);
  png_write_end(png->pngp, NULL);
  fclose(fp);
}

PNG *create_png(int width, int height) {
  PNG *png = (PNG*) malloc(sizeof(PNG));
  png->width = width;
  png->height = height;
  png->pngp = png_create_write_struct(PNG_LIBPNG_VER_STRING,
      NULL, NULL, NULL);
  png->infop = png_create_info_struct(png->pngp);
  png->depth = 8;
  png_set_IHDR(png->pngp, png->infop, width, height,
      png->depth, png->color_type, PNG_INTERLACE_NONE,
      PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_DEFAULT);
  png->data = malloc(height * sizeof(png_bytep));
  png->color = malloc(3 * sizeof(png_byte));
  for (int y = 0; y < height; y++) {
    png->data[y] = malloc(3 * width * sizeof(png_byte));
  }
  return png;
}
