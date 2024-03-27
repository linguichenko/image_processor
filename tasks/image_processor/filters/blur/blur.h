#pragma once
#include "../general_filter/filter.h"

class Blur : public BaseFilter {
private:
    double sigma_;

public:
    explicit Blur(float sigma) : sigma_(sigma){};
    void Apply(Image &image) const override;
};