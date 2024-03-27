#pragma once
#include "../general_filter/filter.h"

class Negative : public BaseFilter {
public:
    Negative(){};
    void Apply(Image &image) const override;
};