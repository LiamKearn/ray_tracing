#pragma once

#include "ray.h"
#include "vec3_defs.h"
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    Point3 p;
    Point3 normal;
    double dist;
} HitRecord;

typedef struct {
    bool (*hit)(void *data, const Ray *ray, double t_min, double t_max,
                HitRecord *record);
    void *data;
} Hittable;

void hittable_free(Hittable *h);
