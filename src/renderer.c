#include "math3d.h"
#include "canvas.h"
#include <stdio.h>

vec3_t project_vertex(vec3_t vertex, mat4_t mvp, int width, int height) {
    vec3_t transformed = apply_transform(mvp, vertex);

    // Perspective division and viewport transform
    vec3_t projected;
    projected.x = (transformed.x + 1.0f) * 0.5f * width;
    projected.y = (1.0f - (transformed.y + 1.0f) * 0.5f) * height;
    projected.z = transformed.z; // for depth sorting
    return projected;
}

int clip_to_circular_viewport(canvas_t *c, float x, float y) {
    float cx = c->width / 2.0f;
    float cy = c->height / 2.0f;
    float radius = (c->width < c->height ? c->width : c->height) / 2.0f;
    float dx = x - cx;
    float dy = y - cy;
    return (dx * dx + dy * dy) <= (radius * radius);
}

void render_wireframe(canvas_t *c, vec3_t *vertices, int vertex_count, int edge_count, int edges[][2], mat4_t mvp) {
    vec3_t projected[128]; // Support up to 128 vertices
    if (vertex_count > 128) vertex_count = 128; // Safety clamp

    // Project each vertex once
    for (int i = 0; i < vertex_count; ++i) {
        projected[i] = project_vertex(vertices[i], mvp, c->width, c->height);
    }

    // Draw edges between projected vertex pairs
    for (int i = 0; i < edge_count; ++i) {
        vec3_t a = projected[edges[i][0]];
        vec3_t b = projected[edges[i][1]];

        if (clip_to_circular_viewport(c, a.x, a.y) && clip_to_circular_viewport(c, b.x, b.y)) {
            draw_line_f(c, a.x, a.y, b.x, b.y, 1.0f);
        }
    }
}

