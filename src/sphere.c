#include "sphere.h"

Hittable *new_sphere(Point3 center, double radius) {
    SphereData *data = malloc(sizeof(SphereData));

    data->center = center;
    data->radius = radius;

    Hittable *h = malloc(sizeof(Hittable));

    h->data = data;
    h->hit = &sphere_hit;

    return h;
}

bool sphere_hit(void *data, const Ray *ray, double t_min, double t_max,
                HitRecord *record) {
    SphereData *s = (SphereData *)data;

    Point3 oc = Point3_subtract(&ray->origin, &s->center);
    double a = Point3_length_squared(&ray->direction);
    double half_b = Point3_dot(&oc, &ray->direction);
    double c = Point3_length_squared(&oc) - (s->radius * s->radius);
    double discriminant = (half_b * half_b) - a * c;

    if (discriminant < 0.0) {
        return false;
    }

    double sqrt_discrim = sqrt(discriminant);
    double root = (-half_b - sqrt_discrim) / a;
    if (root < t_min || t_max < root) {
        root = (-half_b + sqrt_discrim) / a;
        if (root < t_min || t_max < root) {
            return false;
        }
    }

    Point3 hit_loc = ray_extend(ray, root);
    record->dist = root;
    record->hit_location = hit_loc;
    Point3 outward_normal = Point3_cpy_op_divide(
        Point3_subtract(&record->hit_location, &s->center), s->radius);
    hit_record_set_normal_face(record, ray, outward_normal);

    return true;
}
