#pragma once
#include "image.h"

int NormalizeIndex(int x, int n);

class BaseFilter {
public:
    virtual void Apply(Image& image){};
    ~BaseFilter(){};
};

class FilterWithMatrix : BaseFilter{
private:
    float matrix_[3 * 3];

public:
    FilterWithMatrix(){};

    explicit FilterWithMatrix(float* matrix);

    void Apply(Image& image) override;

    ~FilterWithMatrix(){};
};

class Crop : public BaseFilter {
private:
    int width_;
    int height_;
public:
    Crop(int width, int height) : width_(width), height_(height){};
    void Apply(Image &image) override;
};

class Greyscale : BaseFilter {
public:
    void Apply(Image &image) override;
};

class Negative : BaseFilter{
public:
    void Apply(Image &image) override;
};

class Sharp : public FilterWithMatrix {
private:
    float matrix_[9] = {0, -1, 0, -1, 5, -1, 0, -1, 0}; //NOLINT
public:
    void Apply(Image& image) override;
};

class Edges : public FilterWithMatrix {
private:
    float matrix_[9] = {0, -1, 0, -1, 4, -1, 0, -1, 0};  // NOLINT
    float threshold_;
public:
    explicit Edges(float threshold) : threshold_(threshold){};
    void Apply(Image &image) override;
};
