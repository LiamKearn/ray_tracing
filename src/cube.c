#include "cube.h"

bool cube_hit(void *data, const Ray *ray, double t_min, double t_max,
              HitRecord *record) {
    CubeData *x = (CubeData *)data;
    return true;
}

Hittable new_cube(Point3 a, Point3 b) {
    CubeData *data = malloc(sizeof(CubeData));

    data->a = a;
    data->b = b;

    Hittable h = {
        .data = data,
        .hit = &cube_hit,
        .free = &cube_free,
    };

    return h;
}

bool cube_free(void *d) {
    free((CubeData *)d);

    return true;
}
