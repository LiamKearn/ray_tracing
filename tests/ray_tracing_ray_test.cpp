#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../src/ray.h"
#include "../src/vec3_defs.h"

using ::testing::DoubleNear;
using ::testing::ElementsAre;

constexpr double fault_tol = 1e-1;

TEST(ray, simple_extend) {
        Ray init = {
            {1, 2, 3},
            {1, 2, 3},
        };
        // 1 2 3
        // * * *
        // 1 1 1
        // = = =
        // 1 2 3
        // + + +
        // 1 2 3
        // = = =
        // 2 4 6

        Point3 result = ray_extend(&init, 1);
        double result_arr[3] = {};
        Point3_as_array(&result, result_arr);

        ASSERT_THAT(result_arr, ElementsAre(2, 4, 6));
}

TEST(ray, complex_extend) {
        Ray init = {
            {391.12, 6.1, 3.44},
            {4.13, 24.2, 3.31912},
        };
        // 4.13     24.2    3.31912
        // *        *       *
        // 12.4     12.4    12.4
        // =        =       =
        // 51.21    300.0   41.15708
        // +        +       +
        // 391.12   6.1     3.44
        // =        =       =
        // 442.33   306.1   44.59708

        Point3 result = ray_extend(&init, 12.4);
        double result_arr[3] = {};
        Point3_as_array(&result, result_arr);

        ASSERT_THAT(result_arr, ElementsAre(DoubleNear(442.33, fault_tol),
                                            DoubleNear(306.1, fault_tol),
                                            DoubleNear(44.59708, fault_tol)));
}
