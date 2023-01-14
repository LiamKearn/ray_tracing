#include "ray.h"
#include "sphere.h"

RGBColor ray_color(const Ray *ray) {
    Hittable *hs[1] = {new_sphere((Point3){.z = -1}, 0.5)};

    for (size_t i = 0; i < sizeof(hs) / sizeof(Hittable *); i++) {
        Hittable *h = hs[i];
        HitRecord hit_rec = {};
        bool ray_did_intersect_with_hittable =
            h->hit(h->data, ray, 0.0, 10, &hit_rec);

        if (ray_did_intersect_with_hittable) {
            RGBColor normal_shade = *((RGBColor *)&hit_rec.normal);
            assert(fabs(hit_rec.normal.x - normal_shade.x) < DBL_EPSILON);
            assert(fabs(hit_rec.normal.y - normal_shade.y) < DBL_EPSILON);
            assert(fabs(hit_rec.normal.z - normal_shade.z) < DBL_EPSILON);

            RGBColor_op_add(&normal_shade, 1);
            RGBColor_op_multiply(&normal_shade, 0.5);

            return normal_shade;
        }
    }

    // Sky :-)
    RGBColor color_white = {1.0, 1.0, 1.0};
    RGBColor color_blue = {0.5, 0.7, 1.0};

    Point3 dir = ray->direction;
    Point3 unit_direction = Point3_unit_vector(&dir);

    double dist = 0.5 * (unit_direction.y + 1.0);
    double y = 1.0 - dist;
    RGBColor_op_multiply(&color_white, y);
    RGBColor_op_multiply(&color_blue, dist);

    return RGBColor_add(&color_white, &color_blue);
}

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
