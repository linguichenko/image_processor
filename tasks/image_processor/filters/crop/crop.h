#pragma once
#include "../general_filter/filter.h"

class Crop : public BaseFilter {
private:
    int width_;
    int height_;

public:
    Crop(int width, int height) : width_(width), height_(height){};
    void Apply(Image &image) const override;
};