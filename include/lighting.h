#ifndef LIGHTING_H
#define LIGHTING_H

#include "math3d.h"

// Calculate Lambert lighting intensity for an edge defined by start and end points,
// given a light direction vector. Returns value between 0 and 1.
float lambert_intensity(vec3_t start, vec3_t end, vec3_t light_dir);

#endif // LIGHTING_H
