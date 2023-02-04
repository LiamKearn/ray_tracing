#include "ray.h"

Point3 ray_extend(const Ray *t, double dist) {
    // origin + (dist * direction);
    Point3 dir = t->direction;
    Point3_op_multiply(&dir, dist);
    return Point3_add(&t->origin, &dir);
}

void ray_write(FILE *stream, const Ray *r) {
    fprintf(stream, "Origin: %f - %f - %f\nDirection: %f - %f - %f\n\n",
            r->origin.x, r->origin.y, r->origin.z, r->direction.x,
            r->direction.y, r->direction.z);
}
