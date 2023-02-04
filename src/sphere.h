#pragma once

#include "debug_utils.h"
#include "hit_record.h"
#include "hittable.h"
#include "vec3_defs.h"

typedef struct {
    double radius;
    Point3 center;
} SphereData;

bool sphere_hit(void *data, const Ray *ray, double t_min, double t_max,
                HitRecord *record);

Hittable new_sphere(Point3 center, double radius);

bool sphere_free(void *d);
