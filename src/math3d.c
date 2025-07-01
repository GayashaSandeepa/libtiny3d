// importing libraries
#include "math3d.h"
#include <math.h>
#include <stdint.h>

vec3_t vec3_from_spherical(float r, float theta, float phi) {
    vec3_t v;
    v.x = r * sinf(phi) * cosf(theta);
    v.y = r * sinf(phi) * sinf(theta);
    v.z = r * cosf(phi);
    return v;
}

void vec3_to_spherical(vec3_t v, float *r, float *theta, float *phi) {
    float length = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
    if (r) {
        *r = length;
    }

    if (theta) {
        *theta = atan2f(v.y, v.x);
    }

    if (phi) {
        *phi = (length == 0.0f) ? 0.0f : acosf(v.z / length);
    }
}

vec3_t vec3_normalize_fast(vec3_t v) {
    float squared_length = (v.x * v.x + v.y * v.y + v.z * v.z);
    int32_t i;
    float x2, y;
    const float threehalfs = 1.5f;

    x2 = squared_length * 0.5f;
    y = squared_length;
    i = *(int32_t *)&y; 
    i = 0x5f3759df - (i >> 1);
    y = *(float *)&i;
    y = y * (threehalfs - (x2 * y * y));

    v.x *= y;
    v.y *= y;
    v.z *= y;

    return v;
}