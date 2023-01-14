#include "cube.h"
#include "hittable_aggregate.h"
#include "math_util.h"
#include "sphere.h"
#include "vec3_defs.h"

#define IMAGE_WIDTH 800

Point3 world_ray_color(const Ray *ray, const HittableAggregate *world) {
    HitRecord record;

    Point3 color_white = {1.0, 1.0, 1.0};
    Point3 color_blue = {0.5, 0.7, 1.0};

    if (hittable_aggregate_hit(world, ray, 0, INFINITY, &record)) {
        Point3 color = {1, 1, 1};
        Point3_i_add(&color, &record.normal);
        Point3_op_multiply(&color, 0.5);
        return color;
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

    double viewport_height = 2.0;
    double viewport_width = aspect_ratio * viewport_height;
    double focal_length = 1.0;

    Point3 origin = {};
    Point3 horizontal = {.x = viewport_width};
    Point3 vertical = {.y = viewport_height};

    // auto lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0,
    // focal_length);
    Point3 lower_left_corner = origin;
    Point3 h = horizontal;
    Point3 v = vertical;
    Point3_op_divide(&h, 2);
    Point3_op_divide(&v, 2);
    Point3_i_subtract(&lower_left_corner, &h);
    Point3_i_subtract(&lower_left_corner, &v);
    Point3 x = {0, 0, focal_length};
    Point3_i_subtract(&lower_left_corner, &x);

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
            double u = ((double)i) / (IMAGE_WIDTH - 1);
            double v = ((double)j) / (image_height - 1);

            // res = lower_left_corner + u*horizontal + v*vertical - origin
            Point3 uh = Point3_cpy_op_multiply(horizontal, u);
            Point3 vv = Point3_cpy_op_multiply(vertical, v);
            Point3 temp = Point3_add(&uh, &vv);
            Point3 far = Point3_add(&lower_left_corner, &temp);
            Point3 dir = Point3_subtract(&far, &origin);
            Ray r = {origin, dir};

            Point3 temp_pixel = world_ray_color(&r, world);
            RGBColor pixel = *(RGBColor*) &temp_pixel;
            // RGBColor pixel = ray_color(&r);
            rgbcolor_write(stdout, &pixel);
        }
    }
}
