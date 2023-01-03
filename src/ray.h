#include "vec3.h"

typedef struct {
    Point3 origin;
    Vec3 direction;
} Ray;

Point3 ray_at(const Ray *t, const double trav) {
    return (Point3) {0};
}
