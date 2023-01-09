#include "cube.h"

bool cube_hit(void *data, const Ray *ray, double t_min, double t_max,
                const HitRecord *record) {
    CubeData *x = (CubeData *)data;
    VEC3_DEBUG(x->a);
    VEC3_DEBUG(x->b);
    return true;
}

Hittable *new_cube(Point3 a, Point3 b) {
    CubeData *data = malloc(sizeof(CubeData));

    data->a = a;
    data->b = b;

    Hittable *h = malloc(sizeof(Hittable));

    h->data = data;
    h->hit = &cube_hit;

    return h;
}
