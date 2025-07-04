#ifndef RENDERER_H
#define RENDERER_H

#include "canvas.h"
#include "math3d.h"

void render_wireframe(canvas_t *canvas, vec3_t *vertices, int vertex_count, int edges[][2], int edge_count, mat4_t model, mat4_t proj);

#endif
