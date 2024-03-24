#include "image.h"
#include "filter.h"

void Edges(Image & image, float threshold) {
    const int matrix_size = 9;
    float matrix[matrix_size] = {0, -1, 0, -1, 4, -1, 0, -1, 0};
    FilterWithMatrix edge(matrix);
    Greyscale(image);
    edge.Filter(image);
    for (int i = 0; i < image.height_; ++i) {
        for (int j = 0; j < image.width_; ++j) {
            if (image.GetColor(i, j).r > threshold) {
                image.SetColor(1, 1, 1, i, j);
            } else {
                image.SetColor(0, 0, 0, i, j);
            }
        }
    }
}