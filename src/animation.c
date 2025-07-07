//animation.c
#include "math3d.h"

//Cubic Bezier interpolation: B(t) = (1-t)^3*p0 + 3*(1-t)^2*t*p1 + 3*(1-t)*t^2*p2 + t^3*p3
vec3_t vec3_bezier(vec3_t p0,vec3_t p1,vec3_t p2,vec3_t p3,float t){
    float u=1-t;
    float tt=t*t;
    float uu=u*u;
    float uuu=uu*u;
    float ttt=tt*t;

    vec3_t result={
        .x=uuu*p0.x +3*uu *t *p1.x + 3*u*tt *p2.x +ttt *p3.x,
        .y=uuu*p0.y +3*uu *t *p1.y + 3*u*tt *p2.y +ttt *p3.y,
        .z=uuu*p0.z +3*uu *t *p1.z + 3*u*tt *p2.z +ttt *p3.z
    };
    return result;
}
