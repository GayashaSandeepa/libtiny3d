#ifndef MATH3D_H
#define MATH3D_H

typedef struct {
    float x;
    float y;
    float z;

    float r;
    float theta;
    float phi;
} vec3_t;

void update_spherical_coordinates(vec3_t *v);
void update_cartesian_coordinates(vec3_t *v);
vec3_t vec3_from_spherical(float r, float theta, float phi);
vec3_t vec3_normalize_fast(vec3_t v);
vec3_t vec3_slerp(vec3_t a, vec3_t b, float t);

#endif
