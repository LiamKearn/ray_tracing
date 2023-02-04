#pragma once

#include "debug_utils.h"
#include "hittable.h"
#include "vec3_defs.h"

typedef struct {
    Point3 a;
    Point3 b;
} CubeData;

bool cube_hit(void *data, const Ray *ray, double t_min, double t_max,
              HitRecord *record);

Hittable new_cube(Point3 a, Point3 b);

bool cube_free(void *d);
