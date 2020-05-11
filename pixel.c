#include "pixel.h"
#include <stdlib.h>

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

int diffXY(struct Pixel n1, struct Pixel n2) // return difference between coords of 2 pixels 
{
    int diff, xDiff, yDiff;
    xDiff = abs(n1.coords.x - n2.coords.x);
    yDiff = abs(n1.coords.y - n2.coords.y);
    diff = xDiff + yDiff;
    return diff;
}
int diffRGB(struct Pixel n1, struct Pixel n2) // return difference between RGB of 2 pixels
{
    int diff, rDiff, gDiff, bDiff;
    rDiff = abs(n1.RGB.R - n2.RGB.R);
    gDiff = abs(n1.RGB.G - n2.RGB.G);
    bDiff = abs(n1.RGB.B - n2.RGB.B);
    return diff;
}
int comparePixel(struct Pixel n1, struct Pixel n2) // return the weight of difference of 2 pixels
{
    int diffCoord = diffXY(n1, n2);
    if(diffCoord == 0)
    {
        return 0;
    }
    int diff = diffCoord + diffRGB(n1, n2);
    return diff;
}

struct Pixel clusterToPixel(struct Cluster input)
{
    int newX, newY, newR, newG, newB;
    newX = (input.p1.coords.x + input.p1.coords.x)/2;
    newY = (input.p1.coords.x + input.p1.coords.x)/2;
    newR = (input.p1.RGB.R + input.p1.RGB.R)/2;
    newG = (input.p1.RGB.G + input.p1.RGB.G)/2;
    newB = (input.p1.RGB.B + input.p1.RGB.B)/2;
    struct Pixel temp = assignPixel(newX,newY,newR,newG,newB);
    return temp;
}