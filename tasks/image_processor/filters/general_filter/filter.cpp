#include <algorithm>
#include "../../image_creation/image.h"
#include "filter.h"

int NormalizeIndex(int x, int n) {
    return std::clamp(x, 0, n - 1);
}

FilterWithMatrix::FilterWithMatrix(std::vector<std::vector<float>> matrix) {
    matrix_ = matrix;
};

void FilterWithMatrix::ApplyMatrix(Image& image) const {
    std::vector<std::vector<Color>> new_pixels = image.colors_;
    int height = image.GetHeight();
    int width = image.GetWidth();

    const int size_of_kernel = 9;
    const int offsets[size_of_kernel][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 0},
                                            {0, 1}, {1, -1}, {1, 0}, {1, 1}};
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            float red = 0;
            float blue = 0;
            float green = 0;
            int k = 0;
            for (auto [a, b] : offsets) {
                int x = NormalizeIndex(i + a, height);
                int y = NormalizeIndex(j + b, width);
                red += (image.GetColor(x, y)).r * matrix_[k % 3][k / 3];
                blue += (image.GetColor(x, y)).b * matrix_[k % 3][k / 3];
                green += (image.GetColor(x, y)).g * matrix_[k % 3][k / 3];
                ++k;
            }
            red = std::clamp(red, 0.0f, 1.0f);
            green = std::clamp(green, 0.0f, 1.0f);
            blue = std::clamp(blue, 0.0f, 1.0f);
            new_pixels[i][j].r = red;
            new_pixels[i][j].g = green;
            new_pixels[i][j].b = blue;
        }
    }
    image.colors_ = new_pixels;
}
