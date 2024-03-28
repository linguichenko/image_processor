#pragma once
#include "../general_filter/filter.h"

class Glass : public BaseFilter {
private:
    int cell_size_;

public:
    explicit Glass(int cell_size) : cell_size_(cell_size){};
    void Apply(Image &image) const override;
};
