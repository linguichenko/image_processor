#include "../../image_creation/image.h"
#include "negative.h"

void Negative::Apply(Image &image) const {
    for (int i = 0; i < image.GetHeight(); ++i) {
        for (int j = 0; j < image.GetWidth(); ++j) {
            Color curr_color = image.GetColor(i, j);
            float red = 1 - curr_color.r;
            float green = 1 - curr_color.g;
            float blue = 1 - curr_color.b;
            image.SetColor(red, green, blue, i, j);
        }
    }
}
