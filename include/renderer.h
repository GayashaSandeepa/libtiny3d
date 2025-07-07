#ifndef RENDERER_H
#define RENDERER_H

#include "canvas.h"
#include "math3d.h"

// Applying projection and lighting (Lambert) with a given light direction.
void render_wireframe(canvas_t *canvas, vec3_t *vertices, int vertex_count,
                      int edges[][2], int edge_count,
                      mat4_t model, mat4_t proj,
                      vec3_t light_dir);

void render_cube_lit(canvas_t *canvas, vec3_t *vertices, int edges[][2], int edge_count,
                     mat4_t model, mat4_t proj, vec3_t light_dir);

void render_soccerball_lit(canvas_t *canvas, vec3_t *vertices, int vertex_count,
                           int edges[][2], int edge_count, mat4_t model,
                           mat4_t proj, vec3_t light_dir);

// Cube with per-edge normal lighting
void render_cube_lit(canvas_t *canvas, vec3_t *vertices, int edges[][2], int edge_count,
                     mat4_t model, mat4_t proj, vec3_t light_dir);

// Soccer ball with midpoint normal lighting
void render_soccerball_lit(canvas_t *canvas, vec3_t *vertices, int vertex_count,
                           int edges[][2], int edge_count,
                           mat4_t model, mat4_t proj, vec3_t light_dir);

void render_wireframe_zdepth(canvas_t *canvas, vec3_t *vertices, int vertex_count,
                             int edges[][2], int edge_count,
                             mat4_t model, mat4_t proj);

// Projects and renders a basic unlit wireframe model (e.g., for soccer ball)
void render_wireframe_soccer(canvas_t *canvas, vec3_t *vertices, int vertex_count,
                          int edges[][2], int edge_count,
                          mat4_t model, mat4_t proj);

// Renders a lit wireframe using Lambert lighting model (e.g., for lighting demo)
void render_wireframe_lighting(canvas_t *canvas, vec3_t *vertices, int vertex_count,
                               int edges[][2], int edge_count,
                               mat4_t model, mat4_t proj,
                               vec3_t light_dir);

#endif // RENDERER_H
