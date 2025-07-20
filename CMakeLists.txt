cmake_minimum_required(VERSION 3.28)
project(math)

set(CMAKE_CXX_FLAGS "-O3 -std=c++2b")

add_library(math SHARED
    src/Vec2.cpp
)

target_include_directories(math
    PUBLIC include
)

