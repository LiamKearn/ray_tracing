#include "vec3.h"

#ifndef RT_VEC3_H
#define RT_VEC3_H

#define DEF_IMPL_VEC3_METHODS(type, prefix)                                    \
    type prefix##_unit_vector(const type *v) {                                 \
        /* return v * prefix##_length(v) */                                    \
        type copy = *v;                                                        \
        prefix##_op_divide(&copy, prefix##_length(v));                         \
        return copy;                                                           \
    }                                                                          \
    double prefix##_length_squared(const type *v) {                            \
        return (v->x * v->x) + (v->y * v->y) + (v->z * v->z);                  \
    }                                                                          \
    double prefix##_length(const type *v) {                                    \
        return sqrt(prefix##_length_squared(v));                               \
    }                                                                          \
    type prefix##_cross(const type *main, const type *other) {                 \
        type result = {(main->y * other->z) - (main->z * other->y),            \
                       (main->z * other->x) - (main->x * other->z),            \
                       (main->x * other->y) - (main->y * other->x)};           \
                                                                               \
        return result;                                                         \
    }                                                                          \
    double prefix##_dot(const type *main, const type *other) {                 \
        return (main->x * other->x) + (main->y * other->y) +                   \
               (main->z * other->z);                                           \
    }                                                                          \
    void prefix##_i_divide(type *t, const type *other) {                       \
        t->x /= other->x;                                                      \
        t->y /= other->y;                                                      \
        t->z /= other->z;                                                      \
    }                                                                          \
    void prefix##_i_multiply(type *t, const type *other) {                     \
        t->x *= other->x;                                                      \
        t->y *= other->y;                                                      \
        t->z *= other->z;                                                      \
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
    type prefix##_cpy_divide(const type *t, const type *other) {               \
        type result = {                                                        \
            t->x / other->x,                                                   \
            t->y / other->y,                                                   \
            t->z / other->z,                                                   \
        };                                                                     \
                                                                               \
        return result;                                                         \
    }                                                                          \
    type prefix##_cpy_multiply(const type *t, const type *other) {             \
        type result = {                                                        \
            t->x * other->x,                                                   \
            t->y * other->y,                                                   \
            t->z * other->z,                                                   \
        };                                                                     \
                                                                               \
        return result;                                                         \
    }                                                                          \
    type prefix##_cpy_subtract(const type *t, const type *other) {             \
        type result = {                                                        \
            t->x - other->x,                                                   \
            t->y - other->y,                                                   \
            t->z - other->z,                                                   \
        };                                                                     \
                                                                               \
        return result;                                                         \
    }                                                                          \
    type prefix##_cpy_add(const type *t, const type *other) {                  \
        type result = {                                                        \
            t->x + other->x,                                                   \
            t->y + other->y,                                                   \
            t->z + other->z,                                                   \
        };                                                                     \
                                                                               \
        return result;                                                         \
    }                                                                          \
    type prefix##_cpy_op_divide(type t, double value) {                        \
        t.x /= value;                                                          \
        t.y /= value;                                                          \
        t.z /= value;                                                          \
        return t;                                                              \
    }                                                                          \
    type prefix##_cpy_op_multiply(type t, double value) {                      \
        t.x *= value;                                                          \
        t.y *= value;                                                          \
        t.z *= value;                                                          \
        return t;                                                              \
    }                                                                          \
    type prefix##_cpy_op_add(type t, double value) {                           \
        t.x += value;                                                          \
        t.y += value;                                                          \
        t.z += value;                                                          \
        return t;                                                              \
    }                                                                          \
    type prefix##_cpy_op_subtract(type t, double value) {                      \
        t.x -= value;                                                          \
        t.y -= value;                                                          \
        t.z -= value;                                                          \
        return t;                                                              \
    }                                                                          \
    void prefix##_op_divide(type *t, double value) {                           \
        t->x /= value;                                                         \
        t->y /= value;                                                         \
        t->z /= value;                                                         \
    }                                                                          \
    void prefix##_op_multiply(type *t, double value) {                         \
        t->x *= value;                                                         \
        t->y *= value;                                                         \
        t->z *= value;                                                         \
    }                                                                          \
    void prefix##_op_add(type *t, double value) {                              \
        t->x += value;                                                         \
        t->y += value;                                                         \
        t->z += value;                                                         \
    }                                                                          \
    void prefix##_op_subtract(type *t, double value) {                         \
        t->x -= value;                                                         \
        t->y -= value;                                                         \
        t->z -= value;                                                         \
    }                                                                          \
    void prefix##_debug(const type *t) {                                       \
        fprintf(stderr, "%f - %f - %f\n", t->x, t->y, t->z);                   \
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

#endif
