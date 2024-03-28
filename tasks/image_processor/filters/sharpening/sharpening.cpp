#include "../../image_creation/image.h"
#include "sharpening.h"

void Sharp::Apply(Image &image) const {
    ApplyMatrix(image);
}

Sharp::Sharp() {
    const std::vector<std::vector<float>> filter_matrix = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};
    matrix_ = filter_matrix;
}