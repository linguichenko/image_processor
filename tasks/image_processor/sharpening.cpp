#include "image.h"
#include "filter.h"

void Sharp(Image & image) {
    const int matrix_size = 9;
    float matrix[matrix_size] = {0, -1, 0, -1, 5, -1, 0, -1, 0}; //NOLINT
    FilterWithMatrix sharp(matrix);
    sharp.Filter(image);
}