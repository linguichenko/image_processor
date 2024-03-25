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

FilterWithMatrix::FilterWithMatrix(float* matrix) {
    for (int i = 0; i < 9; ++i) { //NOLINT
        matrix_[i] = matrix[i];
    }
    std::cout<<matrix_<<std::endl;
};

void FilterWithMatrix::Apply(Image & image) {
    for (int i = 0; i < image.height_; ++i){
        std::cout<<matrix_[4]<<std::endl;
        for (int j = 0; j < image.width_; ++j){
            float red = 0;
            float blue = 0;
            float green = 0;
            const int size_of_kernel = 9;
            const int dx[size_of_kernel] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
            const int dy[size_of_kernel] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};
            for (int k = 0; k < size_of_kernel; ++k) {
                int x = NormalizeIndex(i + dx[k], image.height_);
                int y = NormalizeIndex(j + dy[k], image.width_);
                red += (image.GetColor(x, y)).r * matrix_[k];
                blue += (image.GetColor(x, y)).g * matrix_[k];
                green += (image.GetColor(x, y)).b * matrix_[k];
            }
            red = std::min(1.f, std::max(0.f, red));
            green = std::min(1.f, std::max(0.f, green));
            blue = std::min(1.f, std::max(0.f, blue));
            image.SetColor(red, green, blue, i, j);
        }
    }
}




