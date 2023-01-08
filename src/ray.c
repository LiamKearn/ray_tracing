#include "ray.h"

double intersection_with_sphere(const Ray *ray, const Point3 *center,
                                double radius) {
    Point3 oc = point3_cpy_subtract(&ray->origin, center);
    double a = point3_length_squared(&ray->direction);
    double half_b = point3_dot(&oc, &ray->direction);
    double c = point3_length_squared(&oc) - (radius * radius);
    double discriminant = (half_b * half_b) - a * c;
    if (discriminant < 0.0) {
        return -1.0;
    } else {
        return (-half_b - sqrt(discriminant)) / a;
    }
}

RGBColor ray_color(const Ray *ray) {
    Point3 sphere_center = {.z = -1};
    double sphere_radius = 0.5;

    double t = intersection_with_sphere(ray, &sphere_center, sphere_radius);
    if (t > 0.0) {
        Point3 hit_point = ray_extend(ray, t);
        Point3 outward_normal = point3_cpy_subtract(&hit_point, &sphere_center);
        Point3 normal = point3_unit_vector(&outward_normal);

        RGBColor normal_shade = *((RGBColor *)&normal);
        assert(fabs(normal.x - normal_shade.x) < DBL_EPSILON);
        assert(fabs(normal.y - normal_shade.y) < DBL_EPSILON);
        assert(fabs(normal.z - normal_shade.z) < DBL_EPSILON);

        rgbcolor_op_add(&normal_shade, 1);
        rgbcolor_op_multiply(&normal_shade, 0.5);

        return normal_shade;
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

Point3 ray_extend(const Ray *t, double dist) {
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
