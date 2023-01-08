#include <assert.h>
#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef RT_VEC3_H
#define RT_VEC3_H

#define VEC3_DEBUG(vec3)                                                       \
    fprintf(stderr, "%s: %f - %f - %f\n", #vec3, vec3.x, vec3.y, vec3.z);

#define FLO_DEBUG(var) fprintf(stderr, "%s: %f\n", #var, var);

#define DEF_VEC3(type, name)                                                   \
    typedef struct {                                                           \
        type x, y, z;                                                          \
    } name;

#define DEF_VEC3_METHODS(type, prefix)                                         \
    type prefix##_unit_vector(const type *v);                                  \
    double prefix##_length_squared(const type *v);                             \
    double prefix##_length(const type *v);                                     \
    double prefix##_dot(const type *main, const type *other);                  \
    type prefix##_cross(const type *main, const type *other);                  \
    void prefix##_i_add(type *t, const type *other);                           \
    void prefix##_i_subtract(type *t, const type *other);                      \
    void prefix##_i_multiply(type *t, const type *other);                      \
    void prefix##_i_divide(type *t, const type *other);                        \
    type prefix##_cpy_divide(const type *t, const type *other);                \
    type prefix##_cpy_multiply(const type *t, const type *other);              \
    type prefix##_cpy_add(const type *t, const type *other);                   \
    type prefix##_cpy_subtract(const type *t, const type *other);              \
    type prefix##_cpy_op_divide(type t, double value);                         \
    type prefix##_cpy_op_multiply(type t, double value);                       \
    type prefix##_cpy_op_add(type t, double value);                            \
    type prefix##_cpy_op_subtract(type t, double value);                       \
    void prefix##_op_divide(type *t, double value);                            \
    void prefix##_op_multiply(type *t, double value);                          \
    void prefix##_op_add(type *t, double value);                               \
    void prefix##_op_subtract(type *t, double value);                          \
    void prefix##_debug(const type *t);                                        \
    void prefix##_as_array(const type *t, double result[3]);

/* ------------------ \\
||       Point3       ||
\\ ------------------ */

DEF_VEC3(double, Point3);

DEF_VEC3_METHODS(Point3, point3);

/* ------------------ \\
||      RGBColor      ||
\\ ------------------ */

#define RGB_MAX 255
#define RGB_MULT (RGB_MAX + 0.999)

DEF_VEC3(double, RGBColor);

DEF_VEC3_METHODS(RGBColor, rgbcolor);

void rgbcolor_write(FILE *stream, const RGBColor *t);

/* ------------------ \\
||        Vec3        ||
\\ ------------------ */

DEF_VEC3(double, Vec3);

DEF_VEC3_METHODS(Vec3, vec3);

#endif
