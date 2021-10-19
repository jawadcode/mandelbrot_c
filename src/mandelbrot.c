#include "mandelbrot.h"
#include "common.h"
#include <SDL2/SDL.h>

inline Complex complex_add(Complex a, Complex b) {
  return (Complex){a.real + b.real, a.imaginary + b.imaginary};
}

inline Complex complex_sub(Complex a, Complex b) {
  return (Complex){a.real - b.real, a.imaginary - b.imaginary};
}

inline Complex complex_mul(Complex a, Complex b) {
  return (Complex){a.real * b.real - a.imaginary * b.imaginary,
                   a.real * b.imaginary + a.imaginary * b.real};
}

inline Complex complex_square(Complex z) {
  return (Complex){z.real * z.real - z.imaginary * z.imaginary,
                   z.real * z.imaginary * 2};
}

inline double complex_abs(Complex z) {
  return sqrt(z.real * z.real + z.imaginary * z.imaginary);
}

int mandelbrot(Complex c) {
  Complex z = {0, 0};
  int n = 0;
  while (complex_abs(z) <= 2 && n < MAX_ITER) {
    z = complex_add(complex_square(z), c);
    n += 1;
  }
  return n;
}
