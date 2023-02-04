#pragma once

#include "hit_record.h"
#include "ray.h"
#include "vec3_defs.h"
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    bool (*hit)(void *data, const Ray *ray, double t_min, double t_max,
                HitRecord *record);
    bool (*free)(void *data);
    void *data;
} Hittable;

RGBColor ray_color(const Ray *ray);

void hittable_free(Hittable *h);
