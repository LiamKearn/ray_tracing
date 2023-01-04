#include "vec3.h"
#include <math.h>
#include <stdio.h>

#define DEF_IMPL_VEC3_METHODS(type, prefix)                                    \
    double prefix##_length_squared(type *v) {                                  \
        return (v->x * v->x) + (v->y * v->y) + (v->z * v->z);                  \
    }                                                                          \
    double prefix##_length(const type *v) {                                    \
        return sqrt(prefix##_length_squared(v));                               \
    }                                                                          \
    void prefix##_debug(const type *t) {                                       \
        fprintf(stderr, "%f-%f-%f\n", t->x, t->y, t->z);                       \
    }                                                                          \
    type prefix##_subtract(const type *t, const type *other) {                 \
        type result = {0};                                                     \
                                                                               \
        result.x = t->x - other->x;                                            \
        result.y = t->y - other->y;                                            \
        result.z = t->z - other->z;                                            \
                                                                               \
        return result;                                                         \
    }                                                                          \
    type prefix##_add(const type *t, const type *other) {                      \
        type result = {0};                                                     \
                                                                               \
        result.x = t->x + other->x;                                            \
        result.y = t->y + other->y;                                            \
        result.z = t->z + other->z;                                            \
                                                                               \
        return result;                                                         \
    }                                                                          \
    type prefix##_multiply(const type *t, const type *other) {                 \
        type result = {0};                                                     \
                                                                               \
        result.x = t->x * other->x;                                            \
        result.y = t->y * other->y;                                            \
        result.z = t->z * other->z;                                            \
                                                                               \
        return result;                                                         \
    }                                                                          \
    void prefix##_i_add(type *t, const type *other) {                          \
        t->x += other->x;                                                      \
        t->y += other->y;                                                      \
        t->z += other->z;                                                      \
    }                                                                          \
    void prefix##_i_subtract(type *t, const type *other) {                     \
        t->x -= other->x;                                                      \
        t->y -= other->y;                                                      \
        t->z -= other->z;                                                      \
    }                                                                          \
    void prefix##_i_multiply(type *t, const type *other) {                     \
        t->x *= other->x;                                                      \
        t->y *= other->y;                                                      \
        t->z *= other->z;                                                      \
    }                                                                          \
    void prefix##_i_divide(type *t, const type *other) {                       \
        t->x /= other->x;                                                      \
        t->y /= other->y;                                                      \
        t->z /= other->z;                                                      \
    }                                                                          \
    double prefix##_dot(const type *main, const type *other) {                 \
        return (main->x * other->x) + (main->y * other->y) +                   \
               (main->z * other->z);                                           \
    }                                                                          \
    type prefix##_cross(const type *main, const type *other) {                 \
        type result = {(main->y * other->z) - (main->z * other->y),            \
                       (main->z * other->x) - (main->x * other->z),            \
                       (main->x * other->y) - (main->y * other->x)};           \
                                                                               \
        return result;                                                         \
    }                                                                          \
    void prefix##_as_array(const type *t, double result[3]) {                  \
        result[0] = t->x;                                                      \
        result[1] = t->y;                                                      \
        result[2] = t->z;                                                      \
    }

/* ------------------ \\
||       Point3       ||
\\ ------------------ */

DEF_IMPL_VEC3_METHODS(Point3, point3);

/* ------------------ \\
||      RGBColor      ||
\\ ------------------ */

DEF_IMPL_VEC3_METHODS(RGBColor, rgbcolor);

void rgbcolor_write(FILE *stream, const RGBColor *t) {
    int x = RGB_MULT * t->x;
    int y = RGB_MULT * t->y;
    int z = RGB_MULT * t->z;

    fprintf(stream, "%d %d %d\n", x, y, z);
}

/* ------------------ \\
||        Vec3        ||
\\ ------------------ */

DEF_IMPL_VEC3_METHODS(Vec3, vec3);
