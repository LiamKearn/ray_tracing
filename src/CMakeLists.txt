add_library(ray_tracing)

target_sources(ray_tracing
    PRIVATE
        main.c
        vec3.c
    PUBLIC
        vec3.h
    )

target_include_directories(ray_tracing
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
    )

add_executable(
    debug
        main.c
        vec3.c
    )
