cmake_minimum_required(VERSION 3.28)
project(math)

set(CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-O3")

add_library(math SHARED
    src/Vec2D.cpp
)

target_include_directories(math
    PUBLIC include
)
