#include <gtest/gtest.h>

extern "C" {
#include "../src/vec3.h"
}

TEST(ray_tracing, simple_dot) {
        Vec3 x = {0};
        vec3_init(&x, 3, 3, 3);
        Vec3 y = {0};
        vec3_init(&y, 2, 7, 1);
        //            3  3  3
        //            *  *  *
        //            2  7  1
        //            =  =  =
        //            6  21 3
        //            + -----
        //            =
        ASSERT_EQ(30, vec3_dot(&x, &y));
}
