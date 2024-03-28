#include "../../image_creation/image.h"
#include "glass.h"

// как будто сквозь дно стакана смотрим -- круто работает, но ноль идей почему, нашла в интернете)

// void Glass::Apply(Image& image) const {
//     std::vector<std::vector<Color>> new_pixels(image.height_, std::vector<Color>(image.width_));
//     for (int y = 0; y < image.height_; y++) {
//         for (int x = 0; x < image.width_; x++) {
//             float nx = (float)x / image.width_ * 2 - 1;
//             float ny = (float)y / image.height_ * 2 - 1;
//             float r2 = nx * nx + ny * ny;
//             float r4 = r2 * r2;
//             float dx = 2 * 0.2f * nx * r2 + 0.1f * nx * r4;
//             float dy = 2 * 0.2f * ny * r2 + 0.1f * ny * r4;
//             float su = (x + dx * image.width_) / image.width_;
//             float sv = (y + dy * image.height_) / image.height_;
//
//             int srcX = std::max(0, std::min(image.width_ - 1, static_cast<int>(su * image.width_)));
//             int srcY = std::max(0, std::min(image.height_ - 1, static_cast<int>(sv * image.height_)));
//
//             new_pixels[y][x] = image.colors_[srcY][srcX];
//         }
//     }
//     image.colors_ = new_pixels;
// }

void Glass::Apply(Image& image) const {
    int height_size = image.height_ / cell_size_ + 1;
    int width_size = image.width_ / cell_size_ + 1;
    std::vector<std::vector<Color>> cells(height_size, std::vector<Color>(width_size));
    std::vector<std::vector<Color>> new_pixels(image.height_, std::vector<Color>(image.width_));
    for (int y = 0; y < height_size; y++) {
        for (int x = 0; x < width_size; x++) {
            float sum_red = 0;
            float sum_green = 0;
            float sum_blue = 0;
            float count = 0;

            for (int i = y * cell_size_; i < (y + 1) * cell_size_ && i < image.height_; ++i) {
                for (int j = x * cell_size_; j < (x + 1) * cell_size_ && j < image.width_; ++j) {
                    sum_red += image.colors_[i][j].r;
                    sum_green += image.colors_[i][j].g;
                    sum_blue += image.colors_[i][j].b;
                    ++count;
                }
            }
            cells[y][x].r = sum_red / count;
            cells[y][x].g = sum_green / count;
            cells[y][x].b = sum_blue / count;
        }
    }
    for (int y = 0; y < image.height_; y++) {
        for (int x = 0; x < image.width_; x++) {
            int x_cell = x / cell_size_;
            int y_cell = y / cell_size_;
            new_pixels[y][x] = cells[y_cell][x_cell];
        }
    }
    image.colors_ = new_pixels;
}