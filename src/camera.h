#pragma once

#include "ray.h"
#include "vec3_defs.h"

// Prefer const pointers.
// Big BOD, better to compute on initialisation
// for something frequently used and not mutated.
typedef struct {
    double aspect_ratio;
    double viewport_height;
    double viewport_width;
    double focal_length;
    Point3 origin;
    Point3 horizontal;
    Point3 vertical;
    Point3 lower_left_corner;
} Camera;

Camera new_camera(double aspect_ratio, double viewport_height,
                  double focal_length);

Ray camera_ray_for_vertical_horizontal_offsets(const Camera *cam, double u,
                                               double v);
