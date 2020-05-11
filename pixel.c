#include "pixel.h"

struct Pixel assignPixel(int newX, int newY, int newR, int newG, int newB)
{
    struct Pixel thisPixel;
    thisPixel.coords.x = newX;
    thisPixel.coords.y = newY;
    thisPixel.RGB.R = newR;
    thisPixel.RGB.G = newG;
    thisPixel.RGB.B = newB;
    return thisPixel;
}

