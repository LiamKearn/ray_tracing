#include "vec3.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define IMAGE_WIDTH 256
#define IMAGE_HEIGHT 256
#define RGB_MAX 255
#define RGB_MULT (255 + 0.999)

int main() {
    Vec3 vec1 = {0};
    Vec3 vec2 = {0};
    vec3_init(&vec1, 3, 3, 3);
    vec3_init(&vec2, 2, 7, 1);

    double out = vec3_dot(&vec1, &vec2);

    fprintf(stderr, "%f", out);
    // vec3_debug(&vec1);
    exit(1);

    // double len = vec3_length(&vec);
    // double len_sq = vec3_length_squared(&vec);
    // vec3_debug(&vec);
    // fprintf(stderr, "%f - %f\n", len, len_sq);

    // Print the file format header.
    fprintf(stdout, "P3\n%d %d\n255\n", IMAGE_WIDTH, IMAGE_HEIGHT);

    // Output RGB tuples to the file seperated by a newlines, rows ltr and then
    // columns.
    for (int j = IMAGE_HEIGHT - 1; j >= 0; --j) {
        fprintf(stderr, "\rScanlines remaining: %d ", j);
        fflush(stderr);
        for (int i = 0; i < IMAGE_WIDTH; ++i) {
            double r = ((double)i) / (IMAGE_WIDTH - 1);
            double g = ((double)j) / (IMAGE_HEIGHT - 1);
            double b = 0.25;

            int ir = ((int)RGB_MULT * r);
            int ig = ((int)RGB_MULT * g);
            int ib = ((int)RGB_MULT * b);

            fprintf(stdout, "%d %d %d\n", ir, ig, ib);
        }
    }
}
