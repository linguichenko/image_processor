#include "image.h"
#include "filter.h"

void Edges::Apply(Image &image) {
    Greyscale greyscale;
    greyscale.Apply(image);
    FilterWithMatrix edge(matrix_);
    edge.Apply(image);
    for (int i = 0; i < image.height_; ++i) {
        for (int j = 0; j < image.width_; ++j) {
            if ((image.GetColor(i, j)).r > threshold_) {
                image.SetColor(1, 1, 1, i, j);
            } else {
                image.SetColor(0, 0, 0, i, j);
            }
        }
    }
}
