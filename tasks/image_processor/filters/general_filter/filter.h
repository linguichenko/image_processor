#pragma once
#include "../../image_creation/image.h"

int NormalizeIndex(int x, int n);

class BaseFilter {
public:
    virtual void Apply(Image &image) const {};
    virtual ~BaseFilter(){};
};

class FilterWithMatrix : BaseFilter {
protected:
    std::vector<std::vector<float>> matrix_;

public:
    FilterWithMatrix(){};

    explicit FilterWithMatrix(std::vector<std::vector<float>> matrix);

    void ApplyMatrix(Image &image) const;

    virtual void ApplySpecial(Image &image) const {};
};
