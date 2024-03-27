#pragma once
#include "../general_filter/filter.h"

class Glass : public BaseFilter {
private:
    double distortion_;

public:
    explicit Glass(double distortion) : distortion_(distortion){};
    void Apply(Image &image) const override;
};
