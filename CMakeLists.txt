cmake_minimum_required(VERSION 3.20)
project(mjc)

add_subdirectory(lib)


file(GLOB_RECURSE sources src/*.cpp include/*.hpp)
set(sources
    src/mj/MjLexer.cpp
    src/mjc/main.cpp
)

add_executable(mjc ${sources})
target_compile_options(mjc PUBLIC -std=c++23 -O2 -Wall -Wextra -pedantic -funsigned-char)
target_include_directories(mjc PUBLIC include)

target_link_libraries(mjc lib)
