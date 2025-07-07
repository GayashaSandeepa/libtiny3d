#ifndef MATH3D_H
#define MATH3D_H

#include <math.h>

typedef struct {
    float x;
    float y;
    float z;
} vec3_t;

typedef struct {
    float x;
    float y;
    float z;
    float w;
} vec4_t;

// ✅ Add this to fix all mat4_t-related errors
typedef struct {
    float m[16];
} mat4_t;

// --- Vector functions ---
vec3_t vec3_from_spherical(float r, float theta, float phi);
vec3_t vec3_normalize_fast(vec3_t v);
vec3_t vec3_slerp(vec3_t a, vec3_t b, float t);
void vec3_to_spherical(vec3_t v, float *r, float *theta, float *phi);

// --- Matrix functions ---
mat4_t mat4_identity(void);
mat4_t mat4_multiply(mat4_t a, mat4_t b);
mat4_t mat4_translate(float tx, float ty, float tz);
mat4_t mat4_scale(float sx, float sy, float sz);
mat4_t mat4_rotate_xyz(float rx, float ry, float rz);
mat4_t mat4_frustum_asymmetric(float left, float right, float bottom, float top, float near, float far);
vec3_t apply_transform(mat4_t m, vec3_t v);

// --- vec4 helpers ---
vec4_t vec4_from_vec3(vec3_t v, float w);
vec4_t mat4_mul_vec4(mat4_t m, vec4_t v);

float vec3_dot(vec3_t a, vec3_t b);

vec3_t vec3_cross(vec3_t a, vec3_t b);

vec3_t vec3_sub(vec3_t a, vec3_t b);

#endif
