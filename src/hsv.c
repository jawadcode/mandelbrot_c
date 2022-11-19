#include <SDL2/SDL.h>

#include "hsv.h"

SDL_Colour hsv_to_rgb(double hue, double saturation, double value) {
    while (hue < 0) {
        hue += 360;
    }
    while (hue >= 360) {
        hue -= 360;
    }

    double red, green, blue;
    if (value <= 0) {
        red = green = blue = 0;
    } else if (saturation <= 0) {
        red = green = blue = value;
    } else {
        double hf = hue / 60.0;
        int i = (int)floor(hf);
        double f = hf - i;
        double pv = value * (1 - saturation);
        double qv = value * (1 - saturation * f);
        double tv = value * (1 - saturation * (1 - f));
        switch (i) {
        case 0:
            red = value;
            green = tv;
            blue = pv;
            break;
        case 1:
            red = qv;
            green = value;
            blue = pv;
            break;
        case 2:
            red = pv;
            green = value;
            blue = tv;
            break;
        case 3:
            red = pv;
            green = qv;
            blue = value;
            break;
        case 4:
            red = tv;
            green = pv;
            blue = value;
            break;
        case 5:
            red = value;
            green = pv;
            blue = qv;
            break;
        case 6:
            red = value;
            green = tv;
            blue = pv;
            break;
        case -1:
            red = value;
            green = pv;
            blue = qv;
            break;
        default:
            red = green = blue = value;
            break;
        }
    }

    return (SDL_Colour){CROP((int)(red * 255.0)), CROP((int)(green * 255.0)),
                        CROP((int)(blue * 255.0)), 255};
}
