#include "../image.h"
#include "../filter.h"

void Negative::Apply(Image &image) const{
    for (int i = 0; i < image.height_; ++i) {
        for (int j = 0; j < image.width_; ++j) {
            float red = 1 - image.GetColor(i, j).r;
            float green = 1 - image.GetColor(i, j).g;
            float blue = 1 - image.GetColor(i, j).b;
            image.SetColor(red, green, blue, i, j);
        }
    }
}
