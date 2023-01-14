#pragma once

#include "hittable.h"
#include "ray.h"
#include "vec3_defs.h"
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    Hittable *children;
    size_t count;
    size_t capacity;
} HittableAggregate;

#define DYN_ARR_PUSH(ha, h)                                                    \
    if ((ha)->count >= (ha)->capacity) {                                       \
        if ((ha)->capacity == 0) {                                             \
            (ha)->capacity = 5;                                                \
        } else {                                                               \
            (ha)->capacity = (ha)->capacity * 2;                               \
        }                                                                      \
        (ha)->children =                                                       \
            realloc((ha)->children, (ha)->capacity * sizeof(*(ha)->children)); \
    }                                                                          \
                                                                               \
    (ha)->children[(ha)->count++] = (h);

bool hittable_aggregate_hit(const HittableAggregate *ha, const Ray *ray,
                            double t_min, double t_max, HitRecord *record);

HittableAggregate *new_hittable_aggregate(void);

Hittable *hittable_aggregate_to_hittable(HittableAggregate *ha);

void hittable_aggregate_free(HittableAggregate *ha);
