#ifndef PIXEL_H
#define PIXEL_H

struct Coordinates {
    int x;
    int y;
} coordinates;

struct Color_Channels {
    int R;
    int G;
    int B;
} colorChan;

struct Pixel {
    struct Coordinates coords; //Contains X,Y coords both from {1-n}
    struct Color_Channels RGB; //Contain Red, Green, Blue channels respectively all from {0-255}
} pixel;

struct Cluster {
    struct Pixel p1;
    struct Pixel p2;
} cluster;

struct Pixel assignPixel(int newX, int newY, int newR, int newG, int newB);

int diffXY(struct Pixel n1, struct Pixel n2); 

int diffRGB(struct Pixel n1, struct Pixel n2);

int comparePixel(struct Pixel n1, struct Pixel n2);

struct Pixel clusterToPixel(struct Cluster input);
#endif