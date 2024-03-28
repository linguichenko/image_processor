#pragma once
#include "../../image_creation/image.h"

int NormalizeIndex(int x, int n);

class BaseFilter {
public:
    virtual void Apply(Image &image) const = 0;
    virtual ~BaseFilter() = default;
};

class FilterWithMatrix : BaseFilter {
protected:
    std::vector<std::vector<float>> matrix_;

public:
    FilterWithMatrix() = default;

    explicit FilterWithMatrix(std::vector<std::vector<float>> matrix);

    void ApplyMatrix(Image &image) const;

    void Apply(Image &image) const override{};
};
