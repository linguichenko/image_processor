#include "image.h"
#include "filter.h"

int NormalizeIndex(int x, int n) {
    if (x < 0) {
        x = 0;
    }
    if (x >= n) {
        x = n - 1;
    }
    return x;
}

FilterWithMatrix::FilterWithMatrix(std::vector<std::vector<float>> matrix) {
    matrix_ = matrix;
};

void FilterWithMatrix::ApplyMatrix(Image& image) const {
    std::vector<std::vector<Color>> new_pixels = image.colors_;

    const int size_of_kernel = 9;
    const int dx[size_of_kernel] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
    const int dy[size_of_kernel] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};
    for (int i = 0; i < image.height_; ++i) {
        for (int j = 0; j < image.width_; ++j) {
            double red = 0;
            double blue = 0;
            double green = 0;
            for (int k = 0; k < size_of_kernel; ++k) {
                int x = NormalizeIndex(i + dx[k], image.height_);
                int y = NormalizeIndex(j + dy[k], image.width_);
                red += (image.GetColor(x, y)).r * matrix_[k % 3][k / 3];
                blue += (image.GetColor(x, y)).b * matrix_[k % 3][k / 3];
                green += (image.GetColor(x, y)).g * matrix_[k % 3][k / 3];
            }
            red = std::min(1.0, std::max(0.0, red));
            green = std::min(1.0, std::max(0.0, green));
            blue = std::min(1.0, std::max(0.0, blue));
            new_pixels[i][j].r = red;
            new_pixels[i][j].g = green;
            new_pixels[i][j].b = blue;
        }
    }
    image.colors_ = new_pixels;
}
