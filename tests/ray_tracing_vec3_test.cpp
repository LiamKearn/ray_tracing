#include <gmock/gmock.h>
#include <gtest/gtest.h>

extern "C" {
#include "../src/vec3.h"
}

using ::testing::DoubleNear;
using ::testing::ElementsAre;

constexpr double fault_tol = 1e-4;

TEST(vec3, simple_dot) {
        Point3 x = {3, 3, 3};
        Point3 y = {2, 7, 1};
        //            3  3  3
        //            *  *  *
        //            2  7  1
        //            =  =  =
        //            6  21 3
        //            +  +  +
        //            =  =  =
        ASSERT_EQ(30, point3_dot(&x, &y));
}

TEST(vec3, complex_dot) {
        Point3 x = {3.115, 5.6, 403.4};
        Point3 y = {2, 7, 1};
        ASSERT_EQ(448.830, point3_dot(&x, &y));
}

TEST(vec3, simple_cross) {
        Point3 x = {3, 3, 3};
        Point3 y = {2, 7, 1};

        Point3 result = point3_cross(&x, &y);
        double result_arr[3] = {0};
        point3_as_array(&result, result_arr);
        ASSERT_THAT(result_arr, ElementsAre(-18, 3, 15));
}

TEST(vec3, complex_cross) {
        Point3 x = {3.41, 4.555, 3.31};
        Point3 y = {2, 31.32901, 10.3};

        Point3 result = point3_cross(&x, &y);
        double result_arr[3] = {0};
        point3_as_array(&result, result_arr);
        ASSERT_THAT(result_arr, ElementsAre(DoubleNear(-56.7825, fault_tol),
                                            DoubleNear(-28.503, fault_tol),
                                            DoubleNear(97.7219, fault_tol)));
}
