#include "ray.h"

Point3 ray_at(Ray *t, const double trav) {
    // origin + (trav * direction);
    Point3 dir = t->direction;
    point3_op_multiply(&dir, trav);
    return point3_multiply(&t->origin, &dir);
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

    RGBColor color_white = {1.0, 1.0, 1.0};
    RGBColor color_blue = {0.5, 0.7, 1.0};

    Point3 dir = ray->direction;
    Point3 unit_direction = point3_unit_vector(&dir);

    double t = 0.5 * (unit_direction.y + 1.0);
    double y = 1.0 - t;
    rgbcolor_op_multiply(&color_white, y);
    rgbcolor_op_multiply(&color_blue, t);

    return rgbcolor_add(&color_a, &color_b);
}
