#ifndef mandelbrot_c_hsv
#define mandelbrot_c_hsv

#include <SDL2/SDL.h>
#define CROP(n) ((n) < 0 ? 0 : (n) > 255 ? 255 : (n))

SDL_Colour hsv_to_rgb(double hue, double saturation, double value);

#endif