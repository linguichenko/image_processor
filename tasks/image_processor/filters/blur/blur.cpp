#include <valarray>
#include "../../image_creation/image.h"
#include "blur.h"

void Blur::Apply(Image &image) const {
    int width = image.GetWidth();
    int height = image.GetHeight();
    std::vector<std::vector<Color>> new_pixels(height, std::vector<Color>(width));
    for (int x = 0; x < height; ++x) {
        for (int y = 0; y < width; ++y) {
            new_pixels[x][y].r = 0;
            new_pixels[x][y].g = 0;
            new_pixels[x][y].r = 0;
            int l = std::max(0, static_cast<int>(x - 3 * sigma_));
            int r = std::min(height, static_cast<int>(x + 3 * sigma_));
            float sum = 0;
            for (int i = l; i < r; ++i) {
                float c = std::exp(-static_cast<float>((x - i) * (x - i) / (2 * sigma_ * sigma_)));
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
    for (int x = 0; x < height; ++x) {
        for (int y = 0; y < width; ++y) {
            new_pixels[x][y].r = 0;
            new_pixels[x][y].g = 0;
            new_pixels[x][y].r = 0;
            int l = std::max(0, static_cast<int>(y - 3 * sigma_));
            int r = std::min(width, static_cast<int>(y + 3 * sigma_));
            float sum = 0;
            for (int i = l; i < r; ++i) {
                float c = std::exp(-static_cast<float>((y - i) * (y - i) / (2 * sigma_ * sigma_)));
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