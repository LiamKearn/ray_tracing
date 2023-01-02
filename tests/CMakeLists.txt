add_executable(
    unit_tests
    Vec3Test.cc
    )

target_link_libraries(unit_tests
    PRIVATE
        ray_tracing
        gtest_main
    )

include(GoogleTest)
gtest_discover_tests(unit_tests
    PROPERTIES
        LABELS "unit"
    DISCOVERY_TIMEOUT
        240
    )
