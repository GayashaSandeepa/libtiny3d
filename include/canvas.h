#ifndef CANVAS_H
#define CANVAS_H

typedef struct {
    int width;
    int height;
    float *pixels; // Pointer to an array of pixel data (RGBA format)
} canvas_t;

#endif