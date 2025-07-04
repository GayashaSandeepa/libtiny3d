#include "math3d.h"
#include "canvas.h"
#include "math3d.h"
#include <math.h>
#include <stdio.h>

// Project a 3D vertex to 2D screen space using model and projection matrices
static int project_vertex(vec3_t v, mat4_t model, mat4_t proj, int w, int h, float *x_out, float *y_out) {
    // Transform model -> world
    vec4_t vm = vec4_from_vec3(v, 1.0f);
    vm = mat4_mul_vec4(model, vm);
    // Transform projection
    vm = mat4_mul_vec4(proj, vm);
    if (vm.w == 0.0f) return 0;
    // Perspective divide
    float nx = vm.x / vm.w;
    float ny = vm.y / vm.w;

    // Convert NDC [-1..1] to screen coordinates
    *x_out = (nx * 0.5f + 0.5f) * (float)(w - 1);
    *y_out = (1.0f - (ny * 0.5f + 0.5f)) * (float)(h - 1);
    return 1;
}

// Draw line with anti-aliasing using canvas function draw_line_f or your own
// For simplicity, let's just call canvas draw_line_f
extern void draw_line_f(canvas_t *c, float x0, float y0, float x1, float y1, float thickness);

void render_wireframe(canvas_t *canvas, vec3_t *vertices, int vertex_count, int edges[][2], int edge_count, mat4_t model, mat4_t proj) {
    // int w = canvas->width;
    // int h = canvas->height;

    // for (int i = 0; i < edge_count; i++) {
    //     int idx0 = edges[i][0];
    //     int idx1 = edges[i][1];
    //     if (idx0 >= vertex_count || idx1 >= vertex_count) continue;

    //     float x0, y0, x1, y1;
    //     if (project_vertex(vertices[idx0], model, proj, w, h, &x0, &y0) &&
    //         project_vertex(vertices[idx1], model, proj, w, h, &x1, &y1)) {
    //         draw_line_f(canvas, x0, y0, x1, y1, 1.0f);
    //     }
    // }

    for (int i = 0; i < edge_count; ++i) {
        int i0 = edges[i][0];
        int i1 = edges[i][1];

        // SAFETY CHECK
        if (i0 < 0 || i0 >= vertex_count || i1 < 0 || i1 >= vertex_count) {
            fprintf(stderr, "Invalid edge index: edge[%d] = {%d, %d}\n", i, i0, i1);
            continue;
        }

        float x0, y0, x1, y1;
        if (!project_vertex(vertices[i0], model, proj, canvas->width, canvas->height, &x0, &y0)) continue;
        if (!project_vertex(vertices[i1], model, proj, canvas->width, canvas->height, &x1, &y1)) continue;

        draw_line_f(canvas, x0, y0, x1, y1, 1.0f);
    }

}
