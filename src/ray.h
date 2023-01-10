#pragma once

#include "vec3_defs.h"
#include <assert.h>
#include <float.h>
#include <math.h>
#include <stdio.h>

typedef struct {
    Point3 origin;
    Point3 direction;
} Ray;

double intersection_with_sphere(const Ray *ray, const Point3 *center,
                                double radius);

Point3 ray_extend(const Ray *t, double trav);

RGBColor ray_color(const Ray *ray);

void ray_write(FILE *stream, const Ray *r);
