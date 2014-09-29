#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "sets.h"

int main(void) {

  uint32_t pallet[] = {
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

  julia_t jopt = {
    1920,
    1080,
    1,
    0,
    0,
    1,
    0,
    350,
    0xffffff,
    pallet,
    sizeof(pallet) / sizeof(int)
  };

  /* mandelbrot_t mopt = { */
  /*   3*1920, */
  /*   3*1080, */
  /*   0.85, */
  /*   -0.5, */
  /*   0, */
  /*   1, */
  /*   0, */
  /*   150, */
  /*   0xffffff, */
  /*   pallet, */
  /*   sizeof(pallet) / sizeof(int) */
  /* }; */

  julia_set(jopt);

  return 0;

}
