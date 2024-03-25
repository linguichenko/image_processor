#include "image.h"
#include "filter.h"

void Sharp::Apply(Image &image) {
    FilterWithMatrix filter(matrix_);
    filter.Apply(image);
}