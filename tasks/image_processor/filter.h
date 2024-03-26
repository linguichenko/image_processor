#pragma once
#include "image.h"

int NormalizeIndex(int x, int n);

class BaseFilter {
public:
    virtual void Apply(Image& image) const = 0;
    virtual ~BaseFilter(){};
};

class FilterWithMatrix : BaseFilter{
protected:
    std::vector<std::vector<float>> matrix_;

public:
    FilterWithMatrix(){};

    explicit FilterWithMatrix(std::vector<std::vector<float>> matrix);

    void ApplyMatrix(Image& image) const;
};

class Crop : public BaseFilter {
private:
    int width_;
    int height_;
public:
    Crop(int width, int height) : width_(width), height_(height){};
    void Apply(Image &image) const override;
};

class Greyscale : BaseFilter {
public:
    void Apply(Image &image) const override;
};

class Negative : BaseFilter{
public:
    void Apply(Image &image) const override;
};


class Sharp : public FilterWithMatrix {
public:
    Sharp();

    void Apply(Image &image) const override;
};

class Edges : public FilterWithMatrix {
private:
    float threshold_;
public:
    explicit Edges(float threshold);
    void Apply(Image &image) const override;
};
