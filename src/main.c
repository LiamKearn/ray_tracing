#include "ray.h"

#define IMAGE_WIDTH 800

int main() {
    /* ------------------ \\
    ||       Image        ||
    \\ ------------------ */

    const double aspect_ratio = 16.0 / 9.0;
    const int image_width = 800;
    const int image_height = (int)image_width / aspect_ratio;

    /* ------------------ \\
    ||       Camera       ||
    \\ ------------------ */

    double viewport_height = 2.0;
    double viewport_width = aspect_ratio * viewport_height;
    double focal_length = 1.0;

    Point3 origin = {0, 0, 0};
    Point3 horizontal = {viewport_width, 0, 0};
    Point3 vertical = {0, viewport_height, 0};

    // auto lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0,
    // focal_length);
    Point3 lower_left_corner = origin;
    Point3 h = horizontal;
    Point3 v = vertical;
    point3_op_divide(&h, 2);
    point3_op_divide(&v, 2);
    point3_i_subtract(&lower_left_corner, &h);
    point3_i_subtract(&lower_left_corner, &v);
    Point3 x = {0, 0, focal_length};
    point3_i_subtract(&lower_left_corner, &x);

    /* ------------------ \\
    ||       Render       ||
    \\ ------------------ */

    // Print the file format header.
    // P3 - format
    // width ' ' height - dimensions for wrapping rows into columns
    // 255 - rgb maximum
    fprintf(stdout, "P3\n%d %d\n%d\n", image_width, image_height, RGB_MAX);

    // Output RGB tuples to the file seperated by a newlines, rows ltr and then
    // columns.
    for (int j = image_height - 1; j >= 0; --j) {
        // fprintf(stderr, "\rScanlines remaining: %d ", j);
        // fflush(stderr);

#pragma unroll(IMAGE_WIDTH / 16)
        for (int i = 0; i < image_width; ++i) {
            double u = ((double)i) / (image_width - 1);
            double v = ((double)j) / (image_height - 1);

            // res = lower_left_corner + u*horizontal + v*vertical - origin
            Point3 uh = point3_cpy_op_multiply(horizontal, u);
            Point3 vv = point3_cpy_op_multiply(vertical, v);
            Point3 temp = point3_cpy_add(&uh, &vv);
            Point3 far = point3_cpy_add(&lower_left_corner, &temp);
            Point3 dir = point3_cpy_subtract(&far, &origin);
            Ray r = {origin, dir};

            RGBColor pixel = ray_color(&r);
            rgbcolor_write(stdout, &pixel);
        }
    }
}
