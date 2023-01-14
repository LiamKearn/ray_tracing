#include "hit_record.h"

void hit_record_set_normal_face(HitRecord *h, const Ray *r,
                                Point3 outward_normal) {
    h->is_front_facing = (Point3_dot(&r->direction, &outward_normal) < 0);
    if (!h->is_front_facing) {
        Point3_negate(&outward_normal);
    }
    h->normal = outward_normal;
}
