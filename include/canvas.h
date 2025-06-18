#ifndef CANVAS_H
#define CANVAS_H

typedef struct {
    int width;
    int height;
    float *pixels;
} canvas_t;

// Function prototypes
canvas_t * create_canvas(int width, int height);
void remove_canvas(canvas_t *canvas);
float get_pixel(canvas_t *canvas, int x, int y);
void set_pixel(canvas_t *canvas, int x, int y, float value);
void set_pixel_f(canvas_t *canvas, float x, float y, float value);
void draw_line_f(canvas_t *canvas, float x0, float y0, float x1, float y1, float thickness);

#endif