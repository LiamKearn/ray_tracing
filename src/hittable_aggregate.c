#include "hittable_aggregate.h"

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

HittableAggregate *new_hittable_aggregate(void) {
    HittableAggregate *data = malloc(sizeof(HittableAggregate));
    return data;
}

Hittable *hittable_aggregate_to_hittable(HittableAggregate *ha) {
    Hittable *h = malloc(sizeof(Hittable));

    h->data = ha;

    return h;
}

// TODO: Almost certain that this dynamic array doesn't work properly :-)
void hittable_aggregate_free(HittableAggregate *ha) { free(ha); }
