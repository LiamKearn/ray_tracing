add_executable(renderer)

target_include_directories(renderer
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    )

target_sources(renderer
    PRIVATE
    ray.c
    hittable.c
    sphere.c
    cube.c
    main.c
    )

target_link_libraries(renderer m vec3 debug_utils)

