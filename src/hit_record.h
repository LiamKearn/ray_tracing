#pragma once

#include "ray.h"
#include "vec3_defs.h"
#include <stdbool.h>

typedef struct {
    Point3 hit_location;
    Point3 normal;
    double dist;
    bool is_front_facing;
} HitRecord;

void hit_record_set_normal_face(HitRecord *h, const Ray *r,
                                Point3 outward_normal);
