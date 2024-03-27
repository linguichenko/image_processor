#pragma once
#include "../general_filter/filter.h"

class Sharp : public FilterWithMatrix {
public:
    Sharp();
    void ApplySpecial(Image &image) const override;
};