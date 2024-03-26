#include <valarray>
#include "../image.h"
#include "../filter.h"

void Blur::Apply(Image &image) const{
    std::vector<std::vector<Color>> new_pixels(image.height_, std::vector<Color>(image.width_));
    for (int x = 0; x < image.height_; ++x) {
        for (int y = 0; y < image.width_; ++y) {
            new_pixels[x][y].r = 0;
            new_pixels[x][y].g = 0;
            new_pixels[x][y].r = 0;
            int l = std::max(0, static_cast<int>(x - 3 * sigma_));
            int r = std::min(image.height_, static_cast<int>(x + 3 * sigma_));
            double sum = 0;
            for (int i = l; i < r; ++i) {
                double c = std::exp(-(x - i) * (x - i) / (2 * sigma_ * sigma_));
                new_pixels[x][y].r += image.GetColor(i, y).r * c;
                new_pixels[x][y].g += image.GetColor(i, y).g * c;
                new_pixels[x][y].b += image.GetColor(i, y).b * c;
                sum += c;
            }
            new_pixels[x][y].r /= sum;
            new_pixels[x][y].g /= sum;
            new_pixels[x][y].b /= sum;
        }
    }
    image.colors_ = new_pixels;
    for (int x = 0; x < image.height_; ++x) {
        for (int y = 0; y < image.width_; ++y) {
            new_pixels[x][y].r = 0;
            new_pixels[x][y].g = 0;
            new_pixels[x][y].r = 0;
            int l = std::max(0, static_cast<int>(y - 3 * sigma_));
            int r = std::min(image.width_, static_cast<int>(y + 3 * sigma_));
            double sum = 0;
            for (int i = l; i < r; ++i) {
                double c = std::exp(-(y - i) * (y - i) / (2 * sigma_ * sigma_));
                new_pixels[x][y].r += image.GetColor(x, i).r * c;
                new_pixels[x][y].g += image.GetColor(x, i).g * c;
                new_pixels[x][y].b += image.GetColor(x, i).b * c;
                sum += c;
            }
            new_pixels[x][y].r /= sum;
            new_pixels[x][y].g /= sum;
            new_pixels[x][y].b /= sum;
        }
    }
    image.colors_ = new_pixels;
}