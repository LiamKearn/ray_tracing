#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "math_util.h"
#include <math.h>
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

    RGBColor a = RGBColor_cpy_op_multiply(*t, scale);

    // Gamma correction of 2.0.
    scale *= 2;
    double r = sqrt(scale * a.x);
    double g = sqrt(scale * a.y);
    double b = sqrt(scale * a.z);

    int red = 256 * clamp(r, 0.0, 0.999);
    int green = 256 * clamp(g, 0.0, 0.999);
    int blue = 256 * clamp(b, 0.0, 0.999);

    fprintf(stream, "%d %d %d\n", red, green, blue);
}

#ifdef __cplusplus
}
#endif
