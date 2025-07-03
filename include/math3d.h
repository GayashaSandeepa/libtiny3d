#ifndef MATH3D_H
#define MATH3D_H
#include <math.h>

typedef struct {
    float x;
    float y;
    float z;

    // float r;
    // float theta;
    // float phi;
} vec3_t;

vec3_t vec3_from_spherical(float r, float theta, float phi);
vec3_t vec3_normalize_fast(vec3_t v);
vec3_t vec3_slerp(vec3_t a, vec3_t b, float t);
void vec3_to_spherical(vec3_t v, float *r, float *theta, float *phi);


typedef struct {
    float m[16];
} mat4_t;

mat4_t mat4_identity(void);
mat4_t mat4_multiply(mat4_t a, mat4_t b);
mat4_t mat4_translate(float tx, float ty, float tz);
mat4_t mat4_scale(float sx, float sy, float sz);
mat4_t mat4_rotate_xyz(float rx, float ry, float rz);
mat4_t mat4_frustum_asymmetric(float left, float right, float bottom, float top, float near, float far);
vec3_t apply_transform(mat4_t m, vec3_t v);


#endif
