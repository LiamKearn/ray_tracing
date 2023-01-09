cmake_minimum_required(VERSION 3.22)

project(RayTracing C CXX)

execute_process(COMMAND git rev-parse --show-toplevel OUTPUT_VARIABLE RAYTRACING_SRC_DIR OUTPUT_STRIP_TRAILING_WHITESPACE)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_C_CLANG_TIDY clang-tidy -checks="*")
set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks="*")

include(GNUInstallDirs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

add_subdirectory(src)

add_subdirectory(inc)

enable_testing()

add_subdirectory(tests)

add_custom_target(format
    COMMAND "${RAYTRACING_SRC_DIR}/format"
    USES_TERMINAL
)
