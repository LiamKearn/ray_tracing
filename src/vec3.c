#include "vec3.h"
#include <math.h>
#include <stdio.h>

void vec3_init(Vec3 *v, double x, double y, double z) {
    v->x = x;
    v->y = y;
    v->z = z;
}

double vec3_length_squared(Vec3 *v) {
    return (v->x * v->x) + (v->y * v->y) + (v->z * v->z);
}

double vec3_length(Vec3 *v) { return sqrt(vec3_length_squared(v)); }

void vec3_debug(const Vec3 *t) {
    fprintf(stderr, "%f-%f-%f\n", t->x, t->y, t->z);
}

Vec3 vec3_subtract(const Vec3 *t, const Vec3 *other) {
    Vec3 result = {0};

    result.x = t->x - other->x;
    result.y = t->y - other->y;
    result.z = t->z - other->z;

    return result;
}

Vec3 vec3_add(const Vec3 *t, const Vec3 *other) {
    Vec3 result = {0};

    result.x = t->x + other->x;
    result.y = t->y + other->y;
    result.z = t->z + other->z;

    return result;
}

Vec3 vec3_multiply(const Vec3 *t, const Vec3 *other) {
    Vec3 result = {0};

    result.x = t->x * other->x;
    result.y = t->y * other->y;
    result.z = t->z * other->z;

    return result;
}

void vec3_i_add(Vec3 *t, const Vec3 *other) {
    t->x += other->x;
    t->y += other->y;
    t->z += other->z;
}

void vec3_i_subtract(Vec3 *t, const Vec3 *other) {
    t->x -= other->x;
    t->y -= other->y;
    t->z -= other->z;
}

void vec3_i_multiply(Vec3 *t, const Vec3 *other) {
    t->x *= other->x;
    t->y *= other->y;
    t->z *= other->z;
}

void vec3_i_divide(Vec3 *t, const Vec3 *other) {
    t->x /= other->x;
    t->y /= other->y;
    t->z /= other->z;
}

double vec3_dot(const Vec3 *main, const Vec3 *other) {
    return (main->x * other->x) + (main->y * other->y) + (main->z * other->z);
}

Vec3 vec3_cross(const Vec3 *main, const Vec3 *other) {
    Vec3 result = {0};

    vec3_init(&result, (main->y * other->z) - (main->z * other->y),
              (main->z * other->x) - (main->x * other->z),
              (main->x * other->y) - (main->y * other->x));

    return result;
}
