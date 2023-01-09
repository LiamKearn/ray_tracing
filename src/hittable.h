#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include "ray.h"
#include "vec3_defs.h"

typedef struct {
    Point3 p;
    Point3 normal;
    double t;
} HitRecord;

typedef struct {
    bool (*hit)(void *data, const Ray *ray, double t_min, double t_max,
                const HitRecord *record);
    void *data;
} Hittable;

void hittable_free(Hittable *h);
