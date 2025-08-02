#include "ImageData.hpp"

void export_stbi_image_free(void *retval_from_stbi_load);

void stbi_image_free(void *);

ImageData::ImageData(unsigned char *data) :
    data_{data},
    ref_cnt_{std::make_shared<std::atomic<int32_t>>(1)}
{}

ImageData::ImageData::ImageData(const ImageData &data) :
    data_{data.data_},
    ref_cnt_{data.ref_cnt_}
{
    // Increase the reference count
    (*ref_cnt_)++;
}

ImageData::~ImageData() {
    if (ref_cnt_->fetch_sub(1) == 1) {
        export_stbi_image_free(data_);
    }
}
