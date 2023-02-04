#include "hittable_aggregate.h"

// In a roundabout way "Take the first successful intersection or 'hit'".
bool hittable_aggregate_hit(const HittableAggregate *ha, const Ray *ray,
                            double t_min, double t_max, HitRecord *record) {
    HitRecord temp_rec;
    bool hit_anything = false;
    double closest_so_far = t_max;

    for (size_t i = 0; i < ha->count; i++) {
        Hittable *h = &ha->children[i];

        if (h->hit(h->data, ray, t_min, closest_so_far, &temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.dist;
            *record = temp_rec;
        }
    }

    return hit_anything;
}

void hittable_aggregate_free(HittableAggregate *ha) {
    for (size_t i = 0; i < ha->count; i++) {
        Hittable h = ha->children[i];
        h.free(h.data);
    }
    free(ha->children);
}
