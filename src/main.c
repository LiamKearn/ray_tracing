#include "camera.h"
#include "cube.h"
#include "hittable_aggregate.h"
#include "math_util.h"
#include "sphere.h"
#include "vec3_defs.h"
#include <stdlib.h>

// Image width given aspect ratio is hardcoded to 16/9.
#define IMAGE_WIDTH 800
// How many times we want to hit a particular pixel to average it's color for
// anti-aliasing.
#define SAMPLES_PER_PIXEL 10
// How many times world_ray_color can recurse.
#define MAX_DEPTH 40

Point3 world_ray_color(const Ray *ray, const HittableAggregate *world,
                       int depth) {
    HitRecord record;

    if (depth <= 0) {
        return (Point3){};
    }

    // If we've intersected with anything (Hittable) in the world
    // (HittableAggregate), if we intersect with multiple objects the one
    // closest to the ray's origin is chosen as the hitrecord.
    if (hittable_aggregate_hit(world, ray, 0.001, INFINITY, &record)) {
        // Recast and recurse from the hit location adjust for normal and offset
        // by a rejection obtained random value. This is diffuse rendering.
        Point3 target = Point3_add(&record.normal, &record.hit_location);
        Point3 rand = Point3_random_in_unit_sphere();
        Point3_i_add(&target, &rand);
        Ray temp = {
            .origin = record.hit_location,
            .direction = Point3_subtract(&target, &record.hit_location),
        };
        Point3 new_color = world_ray_color(&temp, world, depth - 1);
        // Once we unwind from recusion return the approriate color and this
        // will be rendered for the pixel in question.
        return Point3_cpy_op_multiply(new_color, 0.5);
    }

    // Else we need to render a "Beautiful blue"!
    Point3 color_white = {1.0, 1.0, 1.0};
    Point3 color_blue = {0.3, 0.6, 1.0};

    // TODO Learn: Freya Holmér has an excellent video on bezier curves and
    // splines which covers use of LERP:
    // - https://www.youtube.com/watch?v=aVwxzDHniEw (bezier curves)
    // - https://www.youtube.com/watch?v=jvPPXbo87ds (splines)
    // - https://twitter.com/freyaholmer/status/1175925033002254338
    // Better yet simon dev's specific video on LERP:
    // - https://www.youtube.com/watch?v=YJB1QnEmlTs (LERP)
    Point3 unit_direction = Point3_unit_vector(&ray->direction);
    double dist = 0.5 * (unit_direction.y + 0.8);
    double y = 1.0 - dist;
    Point3_op_multiply(&color_white, y);
    Point3_op_multiply(&color_blue, dist);

    return Point3_add(&color_white, &color_blue);
}

int main() {
    /* ------------------ \\
    ||       World        ||
    \\ ------------------ */

    HittableAggregate world = {0};
    DYN_ARR_PUSH(&world,
                 new_sphere((Point3){.x = 0.2, .z = -0.6, .y = -0.4}, 0.1));
    DYN_ARR_PUSH(&world, new_sphere((Point3){.z = -1}, 0.5));
    DYN_ARR_PUSH(&world, new_sphere((Point3){.y = -100.5, .z = -1}, 100));

    /* ------------------ \\
    ||       Camera       ||
    \\ ------------------ */

    Camera camera = new_camera(16.0 / 9.0, 2.0, 1.0);

    /* ------------------ \\
    ||       Image        ||
    \\ ------------------ */

    const int image_height = IMAGE_WIDTH / camera.aspect_ratio;

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

                Ray ray =
                    camera_ray_for_vertical_horizontal_offsets(&camera, u, v);

                Point3 temp_pixel = world_ray_color(&ray, &world, MAX_DEPTH);
                RGBColor pixel = *(RGBColor *)&temp_pixel;

                RGBColor_i_add(&color, &pixel);
            }
            rgbcolor_write(stdout, &color, SAMPLES_PER_PIXEL);
        }
    }

    hittable_aggregate_free(&world);
}
