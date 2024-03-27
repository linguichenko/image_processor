#pragma once
#include "../general_filter/filter.h"

class Greyscale : public BaseFilter {
public:
    void Apply(Image &image) const override;
};
