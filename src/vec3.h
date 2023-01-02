#pragma once

typedef struct {
    double x;
    double y;
    double z;
} Vec3;

void vec3_init(Vec3 *v, double x, double y, double z);

double vec3_length_squared(Vec3 *v);

double vec3_length(Vec3 *v);

double vec3_dot(const Vec3 *main, const Vec3 *other);

Vec3 vec3_cross(const Vec3 *main, const Vec3 *other);

void vec3_debug(const Vec3 *t);

Vec3 vec3_subtract(const Vec3 *t, const Vec3 *other);

Vec3 vec3_add(const Vec3 *t, const Vec3 *other);

Vec3 vec3_multiply(const Vec3 *t, const Vec3 *other);

void vec3_i_add(Vec3 *t, const Vec3 *other);

void vec3_i_subtract(Vec3 *t, const Vec3 *other);

void vec3_i_multiply(Vec3 *t, const Vec3 *other);

void vec3_i_divide(Vec3 *t, const Vec3 *other);


