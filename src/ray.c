#include "ray.h"

double insection_with_sphere(const Ray *ray, const Point3 *center,
                             double radius) {
    Point3 oc = point3_cpy_subtract(&ray->origin, center);
    double a = point3_dot(&ray->direction, &ray->direction);
    double b = 2.0 * point3_dot(&oc, &ray->direction);
    double c = point3_dot(&oc, &oc) - (radius * radius);
    double discriminant = (b * b) - 4 * a * c;
    if (discriminant < 0.0) {
        return -1.0;
    } else {
        return ((-b - sqrt(discriminant)) / (2.0 * a));
    }
}

RGBColor ray_color(const Ray *ray) {
    /*
    CPP REF impl:
    ```
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
    ```
    */

    Point3 center = {0, 0, -1};
    double t = insection_with_sphere(ray, &center, 0.5);
    if (t > 0.0) {
        Point3 subtract = {0, 0, -1};
        Point3 z = ray_extend(ray, t);
        Point3 far_a = point3_cpy_subtract(&z, &subtract);
        Point3 norm = point3_unit_vector(&far_a);
        RGBColor o = *((RGBColor *)&norm);
        rgbcolor_op_add(&o, 1);
        return o;
    }

    RGBColor color_white = {1.0, 1.0, 1.0};
    RGBColor color_blue = {0.5, 0.7, 1.0};

    Point3 dir = ray->direction;
    Point3 unit_direction = point3_unit_vector(&dir);

    t = 0.5 * (unit_direction.y + 1.0);
    double y = 1.0 - t;
    rgbcolor_op_multiply(&color_white, y);
    rgbcolor_op_multiply(&color_blue, t);

    return rgbcolor_cpy_add(&color_white, &color_blue);
}

Point3 ray_extend(const Ray *t, const double dist) {
    // origin + (dist * direction);
    Point3 dir = t->direction;
    point3_op_multiply(&dir, dist);
    return point3_cpy_add(&t->origin, &dir);
}

void ray_write(FILE *stream, const Ray *r) {
    fprintf(stream, "Origin: %f - %f - %f\nDirection: %f - %f - %f\n\n",
            r->origin.x, r->origin.y, r->origin.z, r->direction.x,
            r->direction.y, r->direction.z);
}
