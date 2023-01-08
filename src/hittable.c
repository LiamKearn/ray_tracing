#include "hittable.h"

void hittable_free(Hittable *h) {
    free(h->data);
    free(h);
}
