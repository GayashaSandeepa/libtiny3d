#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "canvas.h"
#include "math3d.h"
#include "renderer.h"

// Generate soccer ball
void generate_soccer_ball(vec3_t **vertices, int *vertex_count, int edges[][2], int *edge_count);

int main(void) {
    const int WIDTH = 512, HEIGHT = 512, FRAME_COUNT = 60;

    // Cube
    vec3_t cube_vertices[8] = {
        {-1, -1, -1}, {1, -1, -1},
        {1,  1, -1}, {-1, 1, -1},
        {-1, -1,  1}, {1, -1,  1},
        {1,  1,  1}, {-1, 1,  1}
    };
    int cube_edges[12][2] = {
        {0,1}, {1,2}, {2,3}, {3,0},
        {4,5}, {5,6}, {6,7}, {7,4},
        {0,4}, {1,5}, {2,6}, {3,7}
    };

    // Soccer ball
    vec3_t *ball_vertices = NULL;
    int ball_vcount = 0, ball_ecount = 0;
    int ball_edges[256][2];
    generate_soccer_ball(&ball_vertices, &ball_vcount, ball_edges, &ball_ecount);

    // Projection matrix
    float near = 1.5f, far = 10.0f, fov = 1.2f;
    float aspect = (float)WIDTH / HEIGHT;
    float top = tanf(fov / 2.0f) * near;
    mat4_t proj = mat4_frustum_asymmetric(-top * aspect, top * aspect, -top, top, near, far);

    // 💡 Light from right side (+X direction)
    vec3_t light_dir = vec3_normalize_fast((vec3_t){1.0f, 0.0f, 0.0f});

    for (int frame = 0; frame < FRAME_COUNT; ++frame) {
        canvas_t *canvas = create_canvas(WIDTH, HEIGHT);
        float t = (float)frame / FRAME_COUNT;
        float angle = t * 2.0f * M_PI;

        mat4_t cube_model = mat4_multiply(
            mat4_translate(-1.5f, 0.0f, -5.0f),
            mat4_rotate_xyz(0.0f, angle, 0.0f)
        );
        mat4_t ball_model = mat4_multiply(
            mat4_translate(1.5f, 0.0f, -5.0f),
            mat4_rotate_xyz(0.0f, angle, 0.0f)
        );

        render_wireframe_lighting(canvas, cube_vertices, 8, cube_edges, 12, cube_model, proj, light_dir);
        render_wireframe_lighting(canvas, ball_vertices, ball_vcount, ball_edges, ball_ecount, ball_model, proj, light_dir);

        char filename[64];
        sprintf(filename, "frame_%03d.pgm", frame);
        save_canvas(canvas, filename);
        remove_canvas(canvas);
        printf("Saved %s\n", filename);
    }

    free(ball_vertices);
    return 0;
}