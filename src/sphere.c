#include "sphere.h"

bool sphere_hit(void *data, const Ray *ray, double t_min, double t_max,
                const HitRecord *record) {
    SphereData *x = (SphereData *)data;
    SCALAR_DEBUG(x->radius);
    VEC3_DEBUG(x->center);
    return true;
}

Hittable *new_sphere(Point3 center, double radius) {
    SphereData *data = malloc(sizeof(SphereData));

    data->center = center;
    data->radius = radius;

    Hittable *h = malloc(sizeof(Hittable));

    h->data = data;
    h->hit = &sphere_hit;

    return h;
}
