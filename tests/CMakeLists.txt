include(FetchContent)
FetchContent_Declare(gtest
  QUIET
  URL https://github.com/google/googletest/archive/release-1.12.1.tar.gz
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(gtest)

add_executable(
    unit_tests
    ray_tracing_vec3_test.cpp
    )

target_link_libraries(unit_tests
    PRIVATE
    ray_tracing
    gtest_main
    gmock
    )

include(GoogleTest)
gtest_discover_tests(unit_tests
    PROPERTIES
    LABELS "unit"
    DISCOVERY_TIMEOUT
    240
    )
