#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include <getopt.h>

#include "viewer.h"
#include "sets.h"

void fail(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  vprintf(fmt, args);
  va_end(args);
  exit(EXIT_FAILURE);
}

typedef enum {
  JULIA,
  MANDELBROT,
  NONE_TYPE
} FRACTAL_TYPE;

static struct option long_options[] = {
  {"type", required_argument, 0, 't'},
  {"height", required_argument, 0, 'h'},
  {"width", required_argument, 0, 'w'},
  {"smooth", 0, 0, 's'},
  {"pallet", 0, 0, 'p'},
  {"iterations", 0, 0, 'i'},
  {"x-offset", 0, 0, 'x'},
  {"y-offset", 0, 0, 'y'},
  {"zoom", 0, 0, 'z'},
  {"colors", 0, 0, 'c'}
};

static uint32_t pallet[] = {
  0x421e0f,
  0x19071a,
  0x09012f,
  0x040449,
  0x000764,
  0x0c2c8a,
  0x1852b1,
  0x397dd1,
  0x86b5e5,
  0xd3ecf8,
  0xf1e9bf,
  0xf8c95f,
  0xffaa00,
  0xcc8000,
  0x995700,
  0x6a3403
};

renderopt_t render_options = {
  500,
  500,
  1,
  0,
  0,
  0,
  0,
  100,
  0xffffff,
  pallet,
  sizeof(pallet) / sizeof(int),
  "output.png"
};

void render_fractal(FRACTAL_TYPE type) {
  switch (type) {
    case JULIA:
      julia_set(render_options);
      break;
    case MANDELBROT:
    case NONE_TYPE:
      mandelbrot_set(render_options);
      break;
  }
  viewer_init();
  load_image(render_options.outfile);
}

FRACTAL_TYPE parse_type(const char *type) {
  if (strcmp(type, "mandelbrot") == 0 || strcmp(type, "m") == 0) {
    return MANDELBROT;
  } else if (strcmp(type, "julia") == 0 || strcmp(type, "j") == 0) {
    return JULIA;
  }
  return 0;
}

double parse_double(const char *str) {
  double result;
  if (!sscanf(str, "%lf", &result)) {
    exit(0);
  }
  return result;
}

int parse_int(const char *str) {
  int result;
  if (!sscanf(str, "%d", &result)) {
    exit(0);
  }
  return result;
}

int main(int argc, char **argv) {

  int opt_index;
  FRACTAL_TYPE type = NONE_TYPE;

  for (int c; (c = getopt_long(argc, argv, ":t:h:w:i:x:y:z:sp", long_options, &opt_index)) != -1;) {
    switch (c) {
      case ':':
        fail("error: argument required for option\n");
        break;
      case 't':
        type = parse_type(optarg);
        break;
      case 's':
        render_options.u_smooth = 1;
        break;
      case 'p':
        render_options.u_pallete = 1;
        break;
      case 'h':
        render_options.height = parse_int(optarg);
        break;
      case 'w':
        render_options.width = parse_int(optarg);
        break;
      case 'x':
        render_options.xoff = parse_double(optarg);
        break;
      case 'y':
        render_options.yoff = parse_double(optarg);
        break;
      case 'z':
        render_options.scale = parse_double(optarg);
        break;
      case 'i':
        render_options.m_iter = parse_int(optarg);
        break;
    }
  }

  if (type != NONE_TYPE) {
    render_fractal(type);
  } else {
    fail("error: fractal type must be specified\n");
  }

  return 0;

}
