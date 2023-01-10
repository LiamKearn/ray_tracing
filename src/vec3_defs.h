#pragma once

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

static inline void rgbcolor_write(FILE *stream, const RGBColor *t) {
    int x = RGB_MULT * t->x;
    int y = RGB_MULT * t->y;
    int z = RGB_MULT * t->z;

    fprintf(stream, "%d %d %d\n", x, y, z);
}
