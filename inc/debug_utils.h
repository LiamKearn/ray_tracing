#pragma once

// clang-format off
#define FMT_STR(type) _Generic((type), \
    int: "%s: %d\n",    \
    float: "%s: %f\n",  \
    double: "%s: %f\n", \
    char: "%s: %c\n", \
    char*: "%s: %s\n", \
    bool: "%s: %d\n", \
    default: "Can't print: %s\n")
// clang-format on

#define SCALAR_DEBUG(var) fprintf(stderr, FMT_STR(var), #var, var)

// clang-format off
#define FMT_STR3(type) _Generic((type), \
    int: "%s: %d - %d - %d\n",    \
    float: "%s: %f - %f - %f\n",  \
    double: "%s: %f - %f - %f\n", \
    char: "%s: %c - %c - %c\n", \
    char*: "%s: %s - %s - %s\n", \
    bool: "%s: %d\n", \
    default: "Can't print: %s\n")
// clang-format on

#define VEC3_DEBUG(vec3)                                                       \
    fprintf(stderr, FMT_STR3(vec3.x), #vec3, vec3.x, vec3.y, vec3.z);

