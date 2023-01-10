#include "hittable_aggregate.h"

bool hittable_aggregate_hit(void *data, const Ray *ray, double t_min,
                            double t_max, HitRecord *record) {
    assert("TODO: IMPL");
    return false;
}

HittableAggregate* new_hittable_aggregate(void) {
    HittableAggregate *data = malloc(sizeof(HittableAggregate));
    return data;
}


Hittable* hittable_aggregate_to_hittable(HittableAggregate* ha) {
    Hittable *h = malloc(sizeof(Hittable));

    h->data = ha;
    h->hit = &hittable_aggregate_hit;

    return h;
}

// TODO: Almost certain that this dynamic array doesn't work properly :-)
void hittable_aggregate_free(HittableAggregate *ha) {
    free(ha);
}
