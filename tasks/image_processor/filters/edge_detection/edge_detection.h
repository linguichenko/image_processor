#pragma once
#include "../general_filter/filter.h"

class Edges : public FilterWithMatrix {
private:
    float threshold_;

public:
    explicit Edges(float threshold);
    void Apply(Image &image) const override;
};