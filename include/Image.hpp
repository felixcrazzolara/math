#pragma once

#include "ImageData.hpp"

#include <string>
#include <cstdint>

class Image {
public:

static Image load(const std::string &file_path);

explicit Image(const ImageData &data, const uint32_t &width, const uint32_t &height,
    const uint8_t &num_channels);

Image(const Image &img);

inline uint32_t width() const noexcept {
    return width_;
}

inline uint32_t height() const noexcept {
    return height_;
}

inline uint8_t num_channels() const noexcept {
    return num_channels_;
}

inline const ImageData& data() const noexcept {
    return data_;
}

private:

ImageData data_;
const uint32_t width_;
const uint32_t height_;
const uint8_t num_channels_;

}; // End of class image
