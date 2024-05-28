cmake_minimum_required(VERSION 3.20)
project(mjc)


#file(GLOB_RECURSE sources src/*.cpp include/*.hpp)
set(sources
    src/mj/MjLexer.cpp
    src/mjc/main.cpp
)

add_executable(mjc ${sources})
target_compile_options(mjc PUBLIC -std=c++20 -O2 -Wall -pedantic)
target_include_directories(mjc PUBLIC include)
