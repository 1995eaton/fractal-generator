#ifndef SETS_H
#define SETS_H

// Smooting algorithm
// http://en.wikipedia.org/wiki/Mandelbrot_set#Escape_time_algorithm
#define ESCAPE_TIME(x,y,i,it) (256 * \
    log2(1.75 + (i) - log2(log2(sqrt((x)*(x)+(y)*(y))))) / log2((double)it));

typedef struct {
  int width;             // Width of the fractal
  int height;            // Height of the fractal
  double scale;          // Zoom factor
  double xoff, yoff;     // X and Y offsets
  bool u_pallete;        // Use the color pallete instead of monochrome colors
  bool u_smooth;         // Use smooth shading
  double m_iter;         // Max iterations for the set
  uint32_t monochrome;   // A monochrome hex color used when u_pallet == false
  uint32_t *pallete;
  size_t pallete_size;
} renderopt_t;

typedef renderopt_t mandelbrot_t;
typedef renderopt_t julia_t;

void julia_set(julia_t opt);
void mandelbrot_set(mandelbrot_t opt);

#endif
