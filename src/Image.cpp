#include "Image.hpp"

#include "fpng.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <atomic>
#include <filesystem>
#include <iostream>
#include <limits>
#include <optional>

std::atomic_flag fpng_was_initialized; // Initializes as false

static std::optional<Image> try_load_with_fpng(const std::string &file_path) {
    // Try to load the image
    std::vector<uint8_t> out;
    uint32_t width;
    uint32_t height;
    uint32_t channels_in_file;
    const uint32_t desired_channels = 3;
    const int ret = fpng::fpng_decode_file(file_path.c_str(), out, width, height, channels_in_file,
        desired_channels);

    // Handle the return code
    if (ret == fpng::FPNG_DECODE_NOT_FPNG) {
        return std::nullopt;
    } else if (ret == fpng::FPNG_DECODE_FAILED_NOT_PNG) {
        return std::nullopt;
    } else {
        std::cerr << "Error in try_load_with_fpng: Got return code " << ret << std::endl;
        exit(-1);
    }
}

Image Image::load(const std::string &file_path) {
    // If necessary, initialize fpng
    if (!std::atomic_flag_test_and_set(&fpng_was_initialized)) {
        fpng::fpng_init();
    }

    // Check that the file exists
    if (!std::filesystem::exists(file_path)) {
        std::cerr << "Error in Image::load: The file " << file_path << " doesn't exist.";
        std::cerr << std::endl;
        exit(-1);
    }

    // Try to load the image with fpng
    std::optional<Image> image = try_load_with_fpng(file_path);
    if (image.has_value()) {
        return image.value();
    }

    // Load the image
    int x, y, n;
    unsigned char *data = stbi_load(file_path.c_str(), &x, &y, &n, 0);

    // Sanity checks
    if (x < 0 || y < 0 || n < 0 || x > std::numeric_limits<uint32_t>::max() ||
        y > std::numeric_limits<uint32_t>::max() || n > std::numeric_limits<uint8_t>::max()) {
        std::cerr << "Error in Image::load: Encountered invalid condition, x = " << x << ", y = ";
        std::cerr << y << ", n = " << n << std::endl;
        exit(-1);
    }

    return Image{data, static_cast<uint32_t>(x), static_cast<uint32_t>(y), static_cast<uint8_t>(n)};
}

Image::Image(unsigned char *data, const uint32_t &width, const uint32_t &height,
        const uint8_t &num_channels) :
    data_{data},
    width_{width},
    height_{height},
    num_channels_{num_channels}
{}

Image::~Image() {
    if (data_) {
        stbi_image_free(data_);
        data_ = nullptr;
    }
}
