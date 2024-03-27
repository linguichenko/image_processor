#include "image.h"

Color::Color() : r(0), g(0), b(0){};

Color::Color(float r, float g, float b) : r(r), g(r), b(r){};

Image::Image(int width, int height) {
    width_ = width;
    height_ = height;
    colors_ = std::vector(height, std::vector<Color>(width));
};

Color Image::GetColor(int x, int y) const {
    return colors_[x][y];
};

void Image::SetColor(float r, float g, float b, int x, int y) {
    colors_[x][y].r = r;
    colors_[x][y].g = g;
    colors_[x][y].b = b;
};

Image Read(const std::string path) {
    std::ifstream f{path, std::ios::in | std::ios::binary};

    FileHeader file_header;
    DIBHeader information_header;
    Image image;

    f.read(reinterpret_cast<char*>(&file_header), sizeof(file_header));
    f.read(reinterpret_cast<char*>(&information_header), sizeof(information_header));
    image.width_ = information_header.width;
    image.height_ = information_header.height;

    image.colors_.assign(image.height_, std::vector<Color>(image.width_));
    const int padding = ((4 - image.width_ * 3 % 4) % 4);

    f.ignore(file_header.offset_data - static_cast<int64_t>(sizeof(information_header)) -
             static_cast<int64_t>(sizeof(file_header)));
    for (int x = 0; x < image.height_; ++x) {
        for (int y = 0; y < image.width_; ++y) {
            unsigned char color[3];
            f.read(reinterpret_cast<char*>(color), 3);

            image.colors_[x][y].r = static_cast<float>(color[2]) / base_values::NUM;
            image.colors_[x][y].g = static_cast<float>(color[1]) / base_values::NUM;
            image.colors_[x][y].b = static_cast<float>(color[0]) / base_values::NUM;
        }
        f.ignore(padding);
    }
    f.close();
    return image;
};

void Write(const Image &image, const std::string path) {
    std::ofstream f;
    f.open(path, std::ios::out | std::ios::binary);

    unsigned char bmp_pad[3] = {0, 0, 0};
    const int padding = ((4 - image.width_ * 3 % 4) % 4);

    const int information_header_size = 40;

    FileHeader file_header;
    DIBHeader information_header;

    file_header.file_type = base_values::FILE_TYPE;
    file_header.file_size = file_header.offset_data + 3 * image.height_ * image.width_ + image.height_ * padding;

    information_header.size = information_header_size;
    information_header.width = image.width_;
    information_header.height = image.height_;

    f.write(reinterpret_cast<char*>(&file_header), sizeof(file_header));
    f.write(reinterpret_cast<char*>(&information_header), sizeof(information_header));

    for (int x = 0; x < image.height_; ++x) {
        for (int y = 0; y < image.width_; ++y) {
            unsigned char r = static_cast<unsigned char>(image.GetColor(x, y).r * base_values::NUM);
            unsigned char g = static_cast<unsigned char>(image.GetColor(x, y).g * base_values::NUM);
            unsigned char b = static_cast<unsigned char>(image.GetColor(x, y).b * base_values::NUM);
            unsigned char color[] = {b, g, r};
            f.write(reinterpret_cast<char*>(color), 3);
        }
        f.write(reinterpret_cast<char*>(bmp_pad), padding);
    }
    f.close();
};
