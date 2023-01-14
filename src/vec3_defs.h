#pragma once

#include "math_util.h"
#include <stdio.h>

#define RGB_MAX 255
#define RGB_MULT (RGB_MAX + 0.999)

// Vector defintions.
#define ALIAS Point3
#define T double
#include "vec3.h"

#define ALIAS RGBColor
#define T double
#include "vec3.h"

static inline void rgbcolor_write(FILE *stream, const RGBColor *t,
                                  int samples_per_pixel) {
    double scale = 1.0 / samples_per_pixel;

    RGBColor a = RGBColor_cpy_op_multiply(t, scale);

    int red = 256 * clamp(a.x, 0.0, 0.999);
    int green = 256 * clamp(a.y, 0.0, 0.999);
    int blue = 256 * clamp(a.z, 0.0, 0.999);

    fprintf(stream, "%d %d %d\n", red, green, blue);
}
