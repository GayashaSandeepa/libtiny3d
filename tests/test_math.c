#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "canvas.h"
#include "math3d.h"

vec3_t apply_transform(mat4_t m, vec3_t v) {
    float x = v.x, y = v.y, z = v.z;
    float w = m.m[3] * x + m.m[7] * y + m.m[11] * z + m.m[15];
    if (w == 0.0f) w = 1.0f;

    vec3_t out;
    out.x = (m.m[0] * x + m.m[4] * y + m.m[8]  * z + m.m[12]) / w;
    out.y = (m.m[1] * x + m.m[5] * y + m.m[9]  * z + m.m[13]) / w;
    out.z = (m.m[2] * x + m.m[6] * y + m.m[10] * z + m.m[14]) / w;

    return out;
}

int main() {
    const int WIDTH = 512, HEIGHT = 512;
    const int FRAME_COUNT = 60;
    const float ROTATION_SPEED = 2.0f * M_PI / FRAME_COUNT; // Full 360° in 60 frames

    vec3_t cube[8] = {
        {-1, -1, -1}, {1, -1, -1},
        {1,  1, -1}, {-1, 1, -1},
        {-1, -1,  1}, {1, -1,  1},
        {1,  1,  1}, {-1, 1,  1}
    };

    int edges[12][2] = {
        {0,1}, {1,2}, {2,3}, {3,0},
        {4,5}, {5,6}, {6,7}, {7,4},
        {0,4}, {1,5}, {2,6}, {3,7}
    };

    for (int frame = 0; frame < FRAME_COUNT; frame++) {
        canvas_t *canvas = create_canvas(WIDTH, HEIGHT);
        float angle = frame * ROTATION_SPEED;

        mat4_t scale = mat4_scale(1.0f, 1.0f, 1.0f);
        mat4_t rotate = mat4_rotate_xyz(0.0f, angle, 0.0f); // Y-axis rotation
        mat4_t translate = mat4_translate(0, 0, -5.0f);
        mat4_t frustum = mat4_frustum_asymmetric(-1, 1, -1, 1, 1, 10);

        mat4_t model = mat4_multiply(translate, mat4_multiply(rotate, scale));
        mat4_t mvp = mat4_multiply(frustum, model);

        vec3_t projected[8];
        for (int i = 0; i < 8; i++) {
            vec3_t p = apply_transform(mvp, cube[i]);
            p.x = (p.x + 1.0f) * 0.5f * WIDTH;
            p.y = (1.0f - (p.y + 1.0f) * 0.5f) * HEIGHT;
            projected[i] = p;
        }

        for (int i = 0; i < 12; i++) {
            int a = edges[i][0];
            int b = edges[i][1];
            draw_line_f(canvas, projected[a].x, projected[a].y, projected[b].x, projected[b].y, 1.2f);
        }

        char filename[64];
        sprintf(filename, "frame_%03d.pgm", frame);
        save_canvas(canvas, filename);
        remove_canvas(canvas);
        printf("Saved %s\n", filename);
    }

    return 0;
}
