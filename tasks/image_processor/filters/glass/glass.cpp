#include "../../image_creation/image.h"
#include "glass.h"

//как будто сквозь дно стакана смотрим -- круто работает, но ноль идей почему, нашла в интернете)

//void Glass::Apply(Image& image) const {
//    std::vector<std::vector<Color>> new_pixels(image.height_, std::vector<Color>(image.width_));
//    for (int y = 0; y < image.height_; y++) {
//        for (int x = 0; x < image.width_; x++) {
//            float nx = (float)x / image.width_ * 2 - 1;
//            float ny = (float)y / image.height_ * 2 - 1;
//            float r2 = nx * nx + ny * ny;
//            float r4 = r2 * r2;
//            float dx = 2 * 0.2f * nx * r2 + 0.1f * nx * r4;
//            float dy = 2 * 0.2f * ny * r2 + 0.1f * ny * r4;
//            float su = (x + dx * image.width_) / image.width_;
//            float sv = (y + dy * image.height_) / image.height_;
//
//            int srcX = std::max(0, std::min(image.width_ - 1, static_cast<int>(su * image.width_)));
//            int srcY = std::max(0, std::min(image.height_ - 1, static_cast<int>(sv * image.height_)));
//
//            new_pixels[y][x] = image.colors_[srcY][srcX];
//        }
//    }
//    image.colors_ = new_pixels;
//}

void Glass::Apply(Image& image) const {
    std::vector<std::vector<Color>> new_pixels(image.height_, std::vector<Color>(image.width_));
    int height = image.height_;
    int width = image.width_;
    double cellSize = distortion_;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int cellX = x / cellSize;
            int cellY = y / cellSize;

            int sumR = 0, sumG = 0, sumB = 0;
            double count = cellSize * cellSize;

            for (int i = cellY * cellSize; i < (cellY + 1) * cellSize && i < height; i++) {
                for (int j = cellX * cellSize; j < (cellX + 1) * cellSize && j < width; j++) {
                    sumR += image.colors_[i][j].r;
                    sumG += image.colors_[i][j].g;
                    sumB += image.colors_[i][j].b;
                }
            }

            new_pixels[y][x].r = sumR / count;
            new_pixels[y][x].g = sumG / count;
            new_pixels[y][x].b = sumB / count;
        }
    }
    image.colors_ = new_pixels;
}