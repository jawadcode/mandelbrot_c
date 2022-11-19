#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>
#include <stdio.h>

#include "common.h"
#include "hsv.h"
#include "mandelbrot.h"

void draw(double real_start, double real_end, double imaginary_start,
          double imaginary_end, unsigned char *pixels) {
    for (int x = 0; x < WINDOW_WIDTH; x++) {
        for (int y = 0; y < WINDOW_HEIGHT; y++) {
            Complex c = {real_start + ((double)x / WINDOW_WIDTH) *
                                          (real_end - real_start),
                         imaginary_start +
                             ((double)y / WINDOW_HEIGHT) *
                                 (imaginary_end - imaginary_start)};

            int iterations = mandelbrot(c);

            double hue = ((double)iterations / MAX_ITER) * 256;
            int saturation = 1;
            int value = iterations < MAX_ITER ? 1 : 0;
            SDL_Colour colour =
                hsv_to_rgb(hue, (double)saturation, (double)value);
            int idx = 4 * (y * WINDOW_WIDTH + x);

            pixels[idx] = colour.b;
            pixels[idx + 1] = colour.g;
            pixels[idx + 2] = colour.r;
        }
    }
}

int main(void) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow(
        "mandelbrot_c", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    SDL_SetWindowTitle(window, "mandelbrot_c");
    SDL_Renderer *renderer =
        SDL_CreateRenderer(window, -1, SDL_RENDERER_TARGETTEXTURE);
    SDL_RenderClear(renderer);

    SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888,
                                             SDL_TEXTUREACCESS_STREAMING,
                                             WINDOW_WIDTH, WINDOW_HEIGHT);
    SDL_Surface *surface =
        SDL_CreateRGBSurface(0, WINDOW_WIDTH, WINDOW_HEIGHT, 24, 0, 0, 0, 0);
    unsigned char *pixels = (unsigned char *)surface->pixels;

    double real_start = -2;
    double real_end = 1;
    double imaginary_start = -1;
    double imaginary_end = 1;
    // set to 0 to trigger the first draw
    double prev_real_end = 0;
    double prev_imaginary_end = 0;
    SDL_Event event;
    bool running = true;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    while (running) {
        int pitch = WINDOW_WIDTH * 4;
        SDL_LockTexture(texture, NULL, (void **)&pixels, &pitch);

        if (prev_real_end != real_end || prev_imaginary_end != imaginary_end) {
            draw(real_start, real_end, imaginary_start, imaginary_end, pixels);
            prev_real_end = real_end;
            prev_imaginary_end = imaginary_end;
        }

        SDL_UnlockTexture(texture);
        SDL_RenderCopyEx(renderer, texture, NULL, NULL, 0.0F, NULL, 0);
        SDL_RenderPresent(renderer);

        if (SDL_PollEvent(&event))
            switch (event.type) {
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    running = false;
                    break;
                case SDLK_r:
                    real_start = -2;
                    real_end = 1;
                    imaginary_start = -1;
                    imaginary_end = 1;
                    break;
                case SDLK_LEFT:
                    real_start -= WIDTH_RATE;
                    real_end -= WIDTH_RATE;
                    break;
                case SDLK_RIGHT:
                    real_start += WIDTH_RATE;
                    real_end += WIDTH_RATE;
                    break;
                case SDLK_UP:
                    imaginary_start -= HEIGHT_RATE;
                    imaginary_end -= HEIGHT_RATE;
                    break;
                case SDLK_DOWN:
                    imaginary_start += HEIGHT_RATE;
                    imaginary_end += HEIGHT_RATE;
                    break;
                case SDLK_KP_PLUS:
                case SDLK_PLUS:
                    real_end -= WIDTH_RATE * 2;
                    imaginary_start += HEIGHT_RATE;
                    imaginary_end -= HEIGHT_RATE;
                    break;
                case SDLK_KP_MINUS:
                case SDLK_MINUS:
                    real_end += WIDTH_RATE * 2;
                    imaginary_start -= HEIGHT_RATE;
                    imaginary_end += HEIGHT_RATE;
                    break;
                }
                break;
            case SDL_QUIT:
                running = false;
                break;
            case SDL_MOUSEWHEEL:
                if (event.wheel.y > 0) {
                    real_end -= WIDTH_RATE * 2;
                    imaginary_start += HEIGHT_RATE;
                    imaginary_end -= HEIGHT_RATE;
                } else {
                    real_end += WIDTH_RATE * 2;
                    imaginary_start -= HEIGHT_RATE;
                    imaginary_end += HEIGHT_RATE;
                }
                break;
            }
    }

    // Free resources because we're good people
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}
