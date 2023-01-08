#include "ray.h"

#ifndef RT_HITTABLE_H
#define RT_HITTABLE_H

typedef struct {
    Point3 p;
    Point3 normal;
    double t;
} HitRecord;

typedef struct {
    bool (*hit)(const Ray *ray, double t_min, double t_max,
                const HitRecord *record, void *data);
    void *data;
} Hittable;

void hittable_free(Hittable *h);

#endif
