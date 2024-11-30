cmake_minimum_required(VERSION 3.20)
project(lib)

file(GLOB_RECURSE sources include/core/*.hpp include/container/*.hpp)

add_library(lib ${sources})
set_target_properties(lib PROPERTIES LINKER_LANGUAGE CXX)
target_compile_options(lib PUBLIC -std=c++23 -O2 -Wall -Wextra -pedantic -funsigned-char)
target_include_directories(lib PUBLIC include)
