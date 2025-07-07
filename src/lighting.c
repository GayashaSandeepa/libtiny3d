#include "math3d.h"
#include <math.h>

// Clamp value between 0 and 1
static float clamp01(float v) {
    if (v < 0.0f) return 0.0f;
    if (v > 1.0f) return 1.0f;
    return v;
}

// Normalize vector
static vec3_t vec3_normalize(vec3_t v) {
    float len = sqrtf(v.x*v.x + v.y*v.y + v.z*v.z);
    if (len > 0.00001f) {
        v.x /= len; 
        v.y /= len; 
        v.z /= len;
    }
    return v;
}

// Compute Lambert intensity of edge vector vs light direction
float lambert_intensity(vec3_t start, vec3_t end, vec3_t light_dir) {
    vec3_t edge_dir = (vec3_t){ end.x - start.x, end.y - start.y, end.z - start.z };
    edge_dir = vec3_normalize(edge_dir);
    light_dir = vec3_normalize(light_dir);

    float dotp = edge_dir.x * light_dir.x + edge_dir.y * light_dir.y + edge_dir.z * light_dir.z;
    return clamp01(dotp);
}
