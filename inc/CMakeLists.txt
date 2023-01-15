add_library(math_util)

target_sources(math_util
    PUBLIC
    math_util.h
    )

set_target_properties(math_util PROPERTIES LINKER_LANGUAGE C)

target_include_directories(math_util
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    )

target_link_libraries(math_util m)

add_library(vec3)

target_sources(vec3
    PUBLIC
    vec3.h
    )

set_target_properties(vec3 PROPERTIES LINKER_LANGUAGE C)

target_include_directories(vec3
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    )

target_link_libraries(vec3 math_util m)

add_library(debug_utils)

target_sources(debug_utils
    PUBLIC
    debug_utils.h
    )

set_target_properties(debug_utils PROPERTIES LINKER_LANGUAGE C)

target_include_directories(debug_utils
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    )
