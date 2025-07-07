#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "canvas.h"
#include "math3d.h"

// Declare generate_soccer_ball somewhere accessible
void generate_soccer_ball(vec3_t **vertices, int *vertex_count, int edges[][2], int *edge_count);


int main() {
    const int WIDTH = 512;
    const int HEIGHT = 512;
    const int FRAME_COUNT = 60;
    const float ROT_SPEED = 2.0f * M_PI / FRAME_COUNT; // Full rotation in 60 frames

    vec3_t *vertices = NULL;
    int vertex_count = 0;
    int edges[128][2];   // Adjust size as needed
    int edge_count = 0;

    generate_soccer_ball(&vertices, &vertex_count, edges, &edge_count);

    for (int frame = 0; frame < FRAME_COUNT; frame++) {
        canvas_t *canvas = create_canvas(WIDTH, HEIGHT);
        if (!canvas) {
            fprintf(stderr, "Failed to create canvas\n");
            free(vertices);
            return 1;
        }

        float angle = frame * ROT_SPEED; // Rotate left to right around Y-axis

        mat4_t scale = mat4_scale(100.0f, 100.0f, 100.0f);
        mat4_t rotate = mat4_rotate_xyz(0, angle, 0); // Rotate on Y axis
        mat4_t translate = mat4_translate(0, 0, -350.0f); // Pull back camera
        mat4_t projection = mat4_frustum_asymmetric(-1,1,-1,1,1,1000);

        mat4_t model = mat4_multiply(translate, mat4_multiply(rotate, scale));
        mat4_t mvp = mat4_multiply(projection, model);

        // Project vertices
        vec3_t projected[128];
        for (int i = 0; i < vertex_count; i++) {
            projected[i] = apply_transform(mvp, vertices[i]);
            projected[i].x = (projected[i].x + 1) * 0.5f * WIDTH;
            projected[i].y = (1 - (projected[i].y + 1) * 0.5f) * HEIGHT;
        }

        // Draw edges (wireframe)
        for (int i = 0; i < edge_count; i++) {
            vec3_t a = projected[edges[i][0]];
            vec3_t b = projected[edges[i][1]];
            draw_line_f(canvas, a.x, a.y, b.x, b.y, 1.0f);
        }

        // Save frame as .pgm
        char filename[64];
        sprintf(filename, "soccer_frame_%03d.pgm", frame);
        save_canvas(canvas, filename);
        remove_canvas(canvas);

        printf("Saved frame %d/%d\n", frame + 1, FRAME_COUNT);
    }

    free(vertices);
    return 0;
}
