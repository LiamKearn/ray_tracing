#include <stdio.h>

#define DEF_VEC3(type, name)                                                   \
    typedef struct {                                                           \
        type x;                                                                \
        type y;                                                                \
        type z;                                                                \
    } name

#define DEF_VEC3_METHODS(type, prefix)                                         \
    double prefix##_length_squared(type *v);                                   \
    double prefix##_length(const type *v);                                     \
    double prefix##_dot(const type *main, const type *other);                  \
    type prefix##_cross(const type *main, const type *other);                  \
    void prefix##_as_array(const type *t, double result[3]);                   \
    void prefix##_debug(const type *t);                                        \
    type prefix##_subtract(const type *t, const type *other);                  \
    type prefix##_add(const type *t, const type *other);                       \
    type prefix##_multiply(const type *t, const type *other);                  \
    void prefix##_i_add(type *t, const type *other);                           \
    void prefix##_i_subtract(type *t, const type *other);                      \
    void prefix##_i_multiply(type *t, const type *other);                      \
    void prefix##_i_divide(type *t, const type *other);

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
