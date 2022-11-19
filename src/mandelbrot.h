#ifndef mandelbrot_c_mandelbrot
#define mandelbrot_c_mandelbrot

typedef struct {
    double real;
    double imaginary;
} Complex;

inline Complex complex_add(Complex a, Complex b);

inline Complex complex_square(Complex z);

inline double complex_abs(Complex z);

int mandelbrot(Complex c);

#endif