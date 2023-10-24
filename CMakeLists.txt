cmake_minimum_required(VERSION 3.25)
project(libycvid LANGUAGES C VERSION 0.1.0)

set(CMAKE_C_STANDARD 99)
add_compile_options(-Wall -Wextra -pedantic -Werror)

FILE(GLOB_RECURSE YCVID_SOURCES source/ source/**)

add_library(ycvid ${YCVID_SOURCES})
target_include_directories(ycvid PUBLIC include)
target_include_directories(ycvid PRIVATE private)

target_include_directories(ycvid PRIVATE dependencies/libycenv/dependencies/libycres/include)
target_include_directories(ycvid PRIVATE dependencies/libycenv/include)

add_subdirectory(dependencies/libycenv)
add_dependencies(ycvid ycenv)