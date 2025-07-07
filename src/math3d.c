// importing libraries
#include "math3d.h"
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

vec3_t vec3_slerp(vec3_t a, vec3_t b, float t) {
    a = vec3_normalize_fast(a);
    b = vec3_normalize_fast(b);

    float dot = a.x * b.x + a.y * b.y + a.z * b.z;

    if (dot > 0.9995f) {
        vec3_t result = {
            .x = a.x + t * (b.x - a.x),
            .y = a.y + t * (b.y - a.y),
            .z = a.z + t * (b.z - a.z)
        };
        return vec3_normalize_fast(result);
    }

    if (dot < -1.0f) {
        dot = -1.0f;
    }
    
    if (dot > 1.0f) {
        dot = 1.0f;
    }

    float theta_0 = acosf(dot);
    float theta = theta_0 * t;
    float sin_theta = sinf(theta);
    float sin_theta_0 = sinf(theta_0);

    float s0 = cosf(theta) - dot * sin_theta / sin_theta_0;
    float s1 = sin_theta / sin_theta_0;

    vec3_t result = {
        .x = s0 * a.x + s1 * b.x,
        .y = s0 * a.y + s1 * b.y,
        .z = s0 * a.z + s1 * b.z
    };
    return result;
}



mat4_t mat4_identity(void) {
    mat4_t m = {0};
    m.m[0] = 1.0f;
    m.m[5] = 1.0f;
    m.m[10] = 1.0f;
    m.m[15] = 1.0f;
    return m;
}

mat4_t mat4_multiply(mat4_t a, mat4_t b) {
    mat4_t result = {0};
    // result = a * b
    // Matrix elements stored column-major: m[column*4 + row]
    for (int col = 0; col < 4; ++col) {
        for (int row = 0; row < 4; ++row) {
            float sum = 0.0f;
            for (int k = 0; k < 4; ++k) {
                // a[row + k*4] * b[k + col*4]
                sum += a.m[row + k*4] * b.m[k + col*4];
            }
            result.m[row + col*4] = sum;
        }
    }
    return result;
}


mat4_t mat4_translate(float tx, float ty, float tz) {
    mat4_t result = mat4_identity();
    result.m[12] = tx;
    result.m[13] = ty;
    result.m[14] = tz;
    return result;
}

mat4_t mat4_scale(float sx, float sy, float sz) {
    mat4_t result = {0};
    result.m[0] = sx;
    result.m[5] = sy;
    result.m[10] = sz;
    result.m[15] = 1.0f;
    return result;
}

mat4_t mat4_rotate_xyz(float rx, float ry, float rz) {
    mat4_t result = mat4_identity();
    float cx = cosf(rx);
    float sx = sinf(rx);
    float cy = cosf(ry);
    float sy = sinf(ry);
    float cz = cosf(rz);
    float sz = sinf(rz);

    mat4_t rxm = mat4_identity();
    rxm.m[5] = cx;
    rxm.m[6] = sx;
    rxm.m[9] = -sx;
    rxm.m[10] = cx;

    mat4_t rym = mat4_identity();
    rym.m[0] = cy;
    rym.m[2] = -sy;
    rym.m[8] = sy;
    rym.m[10] = cy;

    mat4_t rzm = mat4_identity();
    rzm.m[0] = cz;
    rzm.m[1] = sz;
    rzm.m[4] = -sz;
    rzm.m[5] = cz;

    return mat4_multiply(rzm, mat4_multiply(rym, rxm));
}

mat4_t mat4_frustum_asymmetric(float left, float right, float bottom, float top, float near, float far) {
    mat4_t result = {0};
    result.m[0] = (2.0f * near) / (right - left);
    result.m[5] = (2.0f * near) / (top - bottom);
    result.m[8] = (right + left) / (right - left);
    result.m[9] = (top + bottom) / (top - bottom);
    result.m[10] = -(far + near) / (far - near);
    result.m[11] = -1.0f;
    result.m[14] = -(2.0f * far * near) / (far - near);
    return result;
}



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

vec4_t vec4_from_vec3(vec3_t v, float w) {
    vec4_t result = {v.x, v.y, v.z, w};
    return result;
}

vec4_t mat4_mul_vec4(mat4_t m, vec4_t v) {
    vec4_t r;
    r.x = m.m[0] * v.x + m.m[4] * v.y + m.m[8]  * v.z + m.m[12] * v.w;
    r.y = m.m[1] * v.x + m.m[5] * v.y + m.m[9]  * v.z + m.m[13] * v.w;
    r.z = m.m[2] * v.x + m.m[6] * v.y + m.m[10] * v.z + m.m[14] * v.w;
    r.w = m.m[3] * v.x + m.m[7] * v.y + m.m[11] * v.z + m.m[15] * v.w;
    return r;
}

float vec3_dot(vec3_t a, vec3_t b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}


vec3_t vec3_cross(vec3_t a, vec3_t b) {
    return (vec3_t){
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

vec3_t vec3_sub(vec3_t a, vec3_t b) {
    vec3_t result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    return result;
}



