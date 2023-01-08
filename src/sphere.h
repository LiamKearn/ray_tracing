#include "hittable.h"

#ifndef RT_SPHERE_H
#define RT_SPHERE_H

typedef struct {
    double radius;
    Point3 center;
} SphereData;

bool sphere_hit(const Ray *ray, double t_min, double t_max,
                const HitRecord *record, void *data);

Hittable *new_sphere(Point3 center, double radius);

#endif
