cmake_minimum_required(VERSION 3.28)
project(math)

set(CMAKE_CXX_FLAGS "-O3 -std=c++2b")

option(BUILD_MATH_TESTS "Whether to build the tests of the math framework." ON)

if (BUILD_MATH_TESTS)
    add_subdirectory(3rdparty/Catch2)
endif()
add_subdirectory(3rdparty/fpng)

add_library(math SHARED
    3rdparty/fpng/src/fpng.cpp
    src/Image.cpp
    src/ImageData.cpp
    src/Vec2.cpp
)

target_include_directories(math
    PUBLIC include
    PRIVATE 3rdparty/fpng/src
)

target_compile_definitions(math
    PRIVATE SSE=1
)

target_compile_options(math
    PUBLIC -march=native -fno-strict-aliasing -mpclmul
)

if (BUILD_MATH_TESTS)
    add_executable(test_image
        tests/test_image.cpp
    )

    target_link_libraries(test_image
        PRIVATE Catch2::Catch2WithMain
        PRIVATE math
    )

    target_compile_definitions(test_image
        PRIVATE TEST_IMG_DIR="${CMAKE_CURRENT_SOURCE_DIR}/test_imgs/"
    )

    include(CTest)
    include(Catch)
    catch_discover_tests(test_image)
endif()
