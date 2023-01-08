#include "sphere.h"

#define IMAGE_WIDTH 800

void test(void) {
    Ray r = {{}, {}};
    HitRecord hr = {{.y = 4}, {}, 1.0};
    Point3 center = {.z = 39.4, .x = 3.0};
    Hittable *x = new_sphere(center, 1.4);
    void *y = x->data;
    x->hit(&r, 1.0, 1.0, &hr, y);

    hittable_free(x);
}

int main() {
    test();
    return 0;
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

    Point3 origin = {};
    Point3 horizontal = {.x = viewport_width};
    Point3 vertical = {.y = viewport_height};

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
