add_library(engine)

target_sources(engine
    PUBLIC
    ray.c
    hittable.c
    hit_record.c
    hittable_aggregate.c
    sphere.c
    cube.c
    camera.c
    )

target_include_directories(engine
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    )

target_link_libraries(engine vec3 math_util debug_utils m)

add_executable(renderer)

target_sources(renderer
    PRIVATE
    main.c
    )

target_link_libraries(renderer engine)

target_compile_options(renderer PRIVATE -fsanitize=address)
target_link_options(renderer PRIVATE -fsanitize=address)
