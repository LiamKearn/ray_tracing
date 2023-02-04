#ifndef VEC3_H
#define VEC3_H
#include "math_util.h"
#include <math.h>
#endif

#ifndef T
#error "Must define template type T for Vec3"
#endif

#ifndef ALIAS
#error "Must define template type ALIAS for Vec3"
#endif

typedef struct {
    T x, y, z;
} ALIAS;

#define CAT(a, b) a##b

#define PASTE(a, b) CAT(a, b)

#define JOIN(prefix, name) PASTE(prefix, PASTE(_, name))

static inline T JOIN(ALIAS, length_squared)(const ALIAS *v) {
    return (v->x * v->x) + (v->y * v->y) + (v->z * v->z);
}

static inline T JOIN(ALIAS, length)(const ALIAS *v) {
    return sqrt(JOIN(ALIAS, length_squared)(v));
}

static inline ALIAS JOIN(ALIAS, cross)(const ALIAS *main, const ALIAS *other) {
    ALIAS result = {(main->y * other->z) - (main->z * other->y),
                    (main->z * other->x) - (main->x * other->z),
                    (main->x * other->y) - (main->y * other->x)};

    return result;
}

static inline T JOIN(ALIAS, dot)(const ALIAS *main, const ALIAS *other) {
    return (main->x * other->x) + (main->y * other->y) + (main->z * other->z);
}

static inline void JOIN(ALIAS, i_divide)(ALIAS *t, const ALIAS *other) {
    t->x /= other->x;
    t->y /= other->y;
    t->z /= other->z;
}

static inline void JOIN(ALIAS, i_multiply)(ALIAS *t, const ALIAS *other) {
    t->x *= other->x;
    t->y *= other->y;
    t->z *= other->z;
}

static inline void JOIN(ALIAS, i_add)(ALIAS *t, const ALIAS *other) {
    t->x += other->x;
    t->y += other->y;
    t->z += other->z;
}

static inline void JOIN(ALIAS, i_subtract)(ALIAS *t, const ALIAS *other) {
    t->x -= other->x;
    t->y -= other->y;
    t->z -= other->z;
}

static inline ALIAS JOIN(ALIAS, divide)(const ALIAS *t, const ALIAS *other) {
    ALIAS result = {
        t->x / other->x,
        t->y / other->y,
        t->z / other->z,
    };

    return result;
}

static inline ALIAS JOIN(ALIAS, multiply)(const ALIAS *t, const ALIAS *other) {
    ALIAS result = {
        t->x * other->x,
        t->y * other->y,
        t->z * other->z,
    };

    return result;
}

static inline ALIAS JOIN(ALIAS, subtract)(const ALIAS *t, const ALIAS *other) {
    ALIAS result = {
        t->x - other->x,
        t->y - other->y,
        t->z - other->z,
    };

    return result;
}

static inline ALIAS JOIN(ALIAS, add)(const ALIAS *t, const ALIAS *other) {
    ALIAS result = {
        t->x + other->x,
        t->y + other->y,
        t->z + other->z,
    };

    return result;
}

static inline ALIAS JOIN(ALIAS, cpy_op_divide)(ALIAS t, T value) {
    t.x /= value;
    t.y /= value;
    t.z /= value;
    return t;
}

static inline ALIAS JOIN(ALIAS, cpy_op_multiply)(ALIAS t, T value) {
    t.x *= value;
    t.y *= value;
    t.z *= value;
    return t;
}

static inline ALIAS JOIN(ALIAS, cpy_op_add)(ALIAS t, T value) {
    t.x += value;
    t.y += value;
    t.z += value;
    return t;
}

static inline ALIAS JOIN(ALIAS, cpy_op_subtract)(ALIAS t, T value) {
    t.x -= value;
    t.y -= value;
    t.z -= value;
    return t;
}

static inline void JOIN(ALIAS, op_divide)(ALIAS *t, T value) {
    t->x /= value;
    t->y /= value;
    t->z /= value;
}

static inline void JOIN(ALIAS, op_multiply)(ALIAS *t, T value) {
    t->x *= value;
    t->y *= value;
    t->z *= value;
}

static inline void JOIN(ALIAS, op_add)(ALIAS *t, T value) {
    t->x += value;
    t->y += value;
    t->z += value;
}

static inline void JOIN(ALIAS, op_subtract)(ALIAS *t, T value) {
    t->x -= value;
    t->y -= value;
    t->z -= value;
}

static inline void JOIN(ALIAS, as_array)(const ALIAS *t, T result[3]) {
    result[0] = t->x;
    result[1] = t->y;
    result[2] = t->z;
}

static inline ALIAS JOIN(ALIAS, unit_vector)(const ALIAS *v) {
    /* return v *JOIN(ALIAS, length)(v) */
    ALIAS copy = *v;
    JOIN(ALIAS, op_divide)(&copy, JOIN(ALIAS, length)(v));
    return copy;
}

static inline void JOIN(ALIAS, negate)(ALIAS *v) {
    v->x = -(v->x);
    v->y = -(v->y);
    v->z = -(v->z);
}

static inline ALIAS JOIN(ALIAS, random)(void) {
    return (ALIAS){
        rand_double(),
        rand_double(),
        rand_double(),
    };
}

static inline ALIAS JOIN(ALIAS, random_between)(double min, double max) {
    return (ALIAS){
        rand_double_between(min, max),
        rand_double_between(min, max),
        rand_double_between(min, max),
    };
}

static inline ALIAS JOIN(ALIAS, random_in_unit_sphere)(void) {
    while (1) {
        ALIAS p = JOIN(ALIAS, random_between)(-1, 1);
        double r = JOIN(ALIAS, length_squared)(&p);
        if (r >= 1)
            continue;
        return p;
    }
}

static inline ALIAS JOIN(ALIAS, random_unit_vector)(void) {
    ALIAS random = JOIN(ALIAS, random_in_unit_sphere)();
    return JOIN(ALIAS, unit_vector)(&random);
}

#undef T
#undef ALIAS
