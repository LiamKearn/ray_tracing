#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <math.h>
#include <stdlib.h>

static inline double degrees_to_radians(double degrees) {
    return degrees * M_PI / 180.0;
}

static inline double rand_double(void) { return rand() / (RAND_MAX + 1.0); }

static inline double rand_double_between(double min, double max) {
    return min + (max - min) * rand_double();
}

static inline double clamp(double value, double min, double max) {
    if (value < min)
        return min;
    if (value > max)
        return max;
    return value;
}

#ifdef __cplusplus
}
#endif
