#include "../image.h"
#include "../filter.h"

void Crop::Apply(Image &image) const {
    int new_width = std::min(image.width_, width_);
    int new_height = std::min(image.height_, height_);
    std::vector<std::vector<Color> > new_colors(new_height, std::vector<Color>(new_width));
    for (int i = 0; i < new_height; ++i) {
        for (int j = 0; j < new_width; ++j) {
            new_colors[i][j] = image.colors_[i + image.height_ - new_height][j];
        }
    }
    image.colors_ = new_colors;
    image.width_ = new_width;
    image.height_ = new_height;
};
