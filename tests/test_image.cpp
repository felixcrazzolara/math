#include <catch2/catch_test_macros.hpp>

#include "Image.hpp"

#include <string>

TEST_CASE("Test Image::load") {
    const Image image = Image::load(std::string{TEST_IMG_DIR} + "test.png");
    REQUIRE( image.width() == 330 );
    REQUIRE( image.height() == 248 );
    REQUIRE( image.num_channels() == 4 );
}
