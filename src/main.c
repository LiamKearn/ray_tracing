#include "vec3.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define IMAGE_WIDTH 512
#define IMAGE_HEIGHT 512

int main() {
    // Print the file format header.
    // P3 - format
    // width ' ' height - dimensions for wrapping rows into columns
    // 255 - rgb maximum
    fprintf(stdout, "P3\n%d %d\n255\n", IMAGE_WIDTH, IMAGE_HEIGHT);

    // Output RGB tuples to the file seperated by a newlines, rows ltr and then
    // columns.
    for (int j = IMAGE_HEIGHT - 1; j >= 0; --j) {
        fprintf(stderr, "\rScanlines remaining: %d ", j);
        fflush(stderr);

#pragma unroll(IMAGE_WIDTH / 16)
        for (int i = 0; i < IMAGE_WIDTH; ++i) {
            RGBColor pixel = {
                ((double)i) / (IMAGE_WIDTH - 1),
                ((double)j) / (IMAGE_HEIGHT - 1),
                0.25,
            };
            rgbcolor_write(stdout, &pixel);
        }
    }
}
