#pragma once
#include "../general_filter/filter.h"

class Edges : public FilterWithMatrix {
private:
    float threshold_;

public:
    explicit Edges(float threshold);
    void ApplySpecial(Image &image) const override;
};