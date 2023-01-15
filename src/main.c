#include "camera.h"
#include "cube.h"
#include "hittable_aggregate.h"
#include "math_util.h"
#include "sphere.h"
#include "vec3_defs.h"
#include <stdlib.h>

#define IMAGE_WIDTH 1600
#define SAMPLES_PER_PIXEL 10
#define MAX_DEPTH 50

Point3 world_ray_color(const Ray *ray, const HittableAggregate *world,
                       int depth) {
    HitRecord record;

    if (depth <= 0) {
        return (Point3){};
    }

    Point3 color_white = {1.0, 1.0, 1.0};
    Point3 color_blue = {0.5, 0.7, 1.0};

    if (hittable_aggregate_hit(world, ray, 0.001, INFINITY, &record)) {
        Point3 target = Point3_add(&record.normal, &record.hit_location);
        Point3 rand = Point3_random_in_unit_sphere();
        Point3_i_add(&target, &rand);
        Ray temp = {.origin = record.hit_location,
                    .direction =
                        Point3_subtract(&target, &record.hit_location)};
        Point3 new_color = world_ray_color(&temp, world, depth - 1);
        return Point3_cpy_op_multiply(new_color, 0.5);
    }

    Point3 unit_direction = Point3_unit_vector(&ray->direction);
    double dist = 0.5 * (unit_direction.y + 1.0);
    double y = 1.0 - dist;
    Point3_op_multiply(&color_white, y);
    Point3_op_multiply(&color_blue, dist);

    return Point3_add(&color_white, &color_blue);
}

int main() {
    /* ------------------ \\
    ||       Image        ||
    \\ ------------------ */

    const double aspect_ratio = 16.0 / 9.0;
    const int image_height = IMAGE_WIDTH / aspect_ratio;

    /* ------------------ \\
    ||       World        ||
    \\ ------------------ */

    HittableAggregate *world = new_hittable_aggregate();
    DYN_ARR_PUSH(world, *new_sphere((Point3){.z = -1}, 0.5));
    DYN_ARR_PUSH(world, *new_sphere((Point3){.y = -100.5, .z = -1}, 100));

    /* ------------------ \\
    ||       Camera       ||
    \\ ------------------ */

    Camera camera = new_camera(16.0 / 9.0, 2.0, 1.0);

    /* ------------------ \\
    ||       Render       ||
    \\ ------------------ */

    // Print the file format header.
    // P3 - format
    // width ' ' height - dimensions for wrapping rows into columns
    // 255 - rgb maximum
    fprintf(stdout, "P3\n%d %d\n%d\n", IMAGE_WIDTH, image_height, RGB_MAX);

    // Output RGB tuples to the file seperated by a newlines, rows ltr and then
    // columns.
    for (int j = image_height - 1; j >= 0; --j) {
        fprintf(stderr, "\rScanlines remaining: %d ", j);
        fflush(stderr);

#pragma unroll(IMAGE_WIDTH / 16)
        for (int i = 0; i < IMAGE_WIDTH; ++i) {
            RGBColor color = {};
            for (int s = 0; s < SAMPLES_PER_PIXEL; ++s) {
                double u = ((double)i + rand_double()) / (IMAGE_WIDTH - 1);
                double v = ((double)j + rand_double()) / (image_height - 1);

                Ray r =
                    camera_ray_for_vertical_horizontal_offsets(&camera, u, v);

                Point3 temp_pixel = world_ray_color(&r, world, MAX_DEPTH);
                RGBColor pixel = *(RGBColor *)&temp_pixel;

                RGBColor_i_add(&color, &pixel);
            }
            rgbcolor_write(stdout, &color, SAMPLES_PER_PIXEL);
        }
    }
}
