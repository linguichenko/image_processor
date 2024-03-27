#pragma once
#include "image.h"

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

class Crop : public BaseFilter {
private:
    int width_;
    int height_;

public:
    Crop(int width, int height) : width_(width), height_(height){};
    void Apply(Image &image) const override;
};

class Greyscale : public BaseFilter {
public:
    void Apply(Image &image) const override;
};

class Negative : public BaseFilter {
public:
    Negative(){};
    void Apply(Image &image) const override;
};

class Sharp : public FilterWithMatrix {
public:
    Sharp();
    void ApplySpecial(Image &image) const override;
};

class Edges : public FilterWithMatrix {
private:
    float threshold_;

public:
    explicit Edges(float threshold);
    void ApplySpecial(Image &image) const override;
};

class Blur : public BaseFilter {
private:
    double sigma_;

public:
    explicit Blur(float sigma) : sigma_(sigma){};
    void Apply(Image &image) const override;
};

class Glass : public BaseFilter {
private:
    double distortion_;

public:
    explicit Glass(double distortion) : distortion_(distortion){};
    void Apply(Image &image) const override;
};
