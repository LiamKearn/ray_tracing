add_library(ray_tracing)

target_sources(ray_tracing
    PRIVATE
    vec3.c
    PUBLIC
    vec3.h
    )

target_include_directories(ray_tracing
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    )

target_link_libraries(ray_tracing m)

add_executable(debug)

target_sources(debug
    PRIVATE
    main.c
    vec3.c
    )

target_link_libraries(debug m)

