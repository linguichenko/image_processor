#include "../../image_creation/image.h"
#include "../grayscale/greyscale.h"
#include "edge_detection.h"

void Edges::Apply(Image &image) const {
    Greyscale greyscale;
    greyscale.Apply(image);
    ApplyMatrix(image);
    for (int i = 0; i < image.GetHeight(); ++i) {
        for (int j = 0; j < image.GetWidth(); ++j) {
            if ((image.GetColor(i, j)).r > threshold_) {
                image.SetColor(1, 1, 1, i, j);
            } else {
                image.SetColor(0, 0, 0, i, j);
            }
        }
    }
}

Edges::Edges(float threshold) {
    const std::vector<std::vector<float>> filter_matrix = {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}};
    matrix_ = filter_matrix;
    threshold_ = threshold;
}