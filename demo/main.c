#include "canvas.h"
#include "math3d.h"
#include "renderer.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define WIDTH 500
#define HEIGHT 500
#define FRAME_COUNT 60

void generate_soccer_ball(vec3_t **vertices, int *vertex_count, int edges[][2], int *edge_count);

int main(void) {
    // ---------------------------
    // Part 1: Draw clock lines
    // ---------------------------
    canvas_t *canvas = create_canvas(WIDTH, HEIGHT);
    if (!canvas) {
        fprintf(stderr, "Failed to create canvas.\n");
        return 1;
    }

    const float c_x = WIDTH / 2.0f;
    const float c_y = HEIGHT / 2.0f;

    for (int angle = 0; angle < 360; angle += 15) {
        float rad = angle * M_PI / 180.0f;
        float x = c_x + 200.0f * cosf(rad);
        float y = c_y + 200.0f * sinf(rad);
        draw_line_f(canvas, c_x, c_y, x, y, 1.5f);
    }

    save_canvas(canvas, "clock_lines.pgm");
    printf("Saved: clock_lines.pgm\n");

    // ---------------------------
    // Part 2: Render soccer ball animation
    // ---------------------------
    vec3_t *vertices = NULL;
    int vertex_count = 0;
    int edges[256][2];
    int edge_count = 0;

    generate_soccer_ball(&vertices, &vertex_count, edges, &edge_count);
    printf("Soccer ball generated: %d vertices, %d edges\n", vertex_count, edge_count);

    for (int frame = 0; frame < FRAME_COUNT; ++frame) {
        printf("Rendering frame %d\n", frame);

        // Destroy old canvas and create a new one for each frame
        remove_canvas(canvas);
        canvas = create_canvas(WIDTH, HEIGHT);
        if (!canvas) {
            fprintf(stderr, "Failed to recreate canvas for frame %d.\n", frame);
            break;
        }

        float angle = (float)frame * 2.0f * M_PI / FRAME_COUNT;
        mat4_t rot = mat4_rotate_xyz(0.0f, angle, 0.0f);
        mat4_t scale = mat4_scale(1.5f, 1.5f, 1.5f);   // Scale up 1.5x
        mat4_t trans = mat4_translate(0.0f, 0.0f, -4.0f); // Move closer than before

        // Combine scale and rotation first, then translate
        mat4_t model = mat4_multiply(trans, mat4_multiply(rot, scale));

        mat4_t proj = mat4_frustum_asymmetric(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 10.0f);

        render_wireframe(canvas, vertices, vertex_count, edges, edge_count, model, proj);

        char filename[64];
        sprintf(filename, "frame_%03d.pgm", frame);
        save_canvas(canvas, filename);
        printf("Saved: %s\n", filename);
    }

    free(vertices);
    remove_canvas(canvas);
    return 0;
}
