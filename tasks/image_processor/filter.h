#pragma once
#include "image.h"

int NormalizeIndex(int x, int n);

class FilterWithMatrix {
private:
    float matrix_[3 * 3];

public:
    explicit FilterWithMatrix(float* matrix);

    void FilterPixel(Image image, int i, int j);

    void Filter(Image& image);
};

void Crop(Image & image, int width, int height);
