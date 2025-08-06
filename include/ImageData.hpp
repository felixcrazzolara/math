#pragma once

#include <atomic>
#include <cstdint>
#include <memory>

class ImageData {
public:

explicit ImageData(unsigned char *data);

explicit ImageData(const ImageData &data);

~ImageData();

inline int32_t ref_count() const noexcept {
    return ref_cnt_->load();
}

inline unsigned char* data() const noexcept {
    return data_;
}

private:

unsigned char *data_;

const std::shared_ptr<std::atomic<int32_t>> ref_cnt_;

}; // End of class ImageData
