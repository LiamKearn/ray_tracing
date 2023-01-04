#include "vec3.h"

typedef struct {
    Point3 origin;
    Point3 direction;
} Ray;

Point3 ray_at(Ray *t, const double trav);

RGBColor ray_color(const Ray *ray);
