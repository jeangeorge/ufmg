cmake_minimum_required(VERSION 3.14)
project(tp2_ed)

set(CMAKE_CXX_STANDARD 14)

add_executable(tp2_ed main.cpp Insertionsort.hpp Stack.hpp Quicksort.cpp Quicksort.hpp Insertionsort.cpp Stack.cpp Cell.cpp Cell.hpp Utils.cpp Utils.hpp)

MATH(EXPR stack_size "16 * 1024 * 1024 * 64") # 1024 Mb
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--stack,${stack_size}")