#include "image.h"


Color::Color() : r(0), g(0), b(0) {};

Color::Color(float r, float g, float b) : r(r), g(r), b(r) {};

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

void Image::Read(const std::string path) {
    std::ifstream f{path, std::ios::in | std::ios::binary};

    std::cout << path << std::endl;

    FileHeader file_header;
    DIBHeader information_header;

    f.read(reinterpret_cast<char*>(&file_header), sizeof(file_header));
    f.read(reinterpret_cast<char*>(&information_header), sizeof(information_header));
    std::cout << file_header.file_type<< ' ' << file_header.file_size << ' ' << file_header.offset_data << ' ' << file_header.unused << std::endl;
    std::cout << information_header.width << ' ' << information_header.height << ' ' << information_header.size;
    width_ = information_header.width;
    height_ = information_header.height;

    colors_.assign(height_, std::vector<Color>(width_));
    const int padding = ((4 - width_ * 3 % 4) % 4);

    f.ignore( file_header.offset_data - sizeof(information_header) - sizeof(file_header));
    std::cout << height_ << ' ' << width_<< ' ';
    for (int x = 0; x < height_; ++x) {
        for (int y = 0; y < width_; ++y) {
            unsigned char color[3];
            f.read(reinterpret_cast<char*>(color), 3);

            colors_[x][y].r = static_cast<float>(color[2]) / base_values::NUM;
            colors_[x][y].g = static_cast<float>(color[1]) / base_values::NUM;
            colors_[x][y].b = static_cast<float>(color[0]) / base_values::NUM;
        }
        std::cout << x << std::endl;
        f.ignore(padding);
        std::cout << x << std::endl;
    }
    std::cout << "aaaa" << std::endl;
    f.close();
};

void Image::Write(const std::string path) const {
    std::ofstream f;
    f.open(path, std::ios::out | std::ios::binary);

    unsigned char bmp_pad[3] = {0, 0, 0};
    const int padding = ((4 - width_ * 3 % 4) % 4);

    const int information_header_size = 40;

    FileHeader file_header;
    DIBHeader information_header;

    file_header.file_type = base_values::FILE_TYPE;
    file_header.file_size = file_header.offset_data + 3 * height_ * width_ + height_ * padding;

    information_header.size = information_header_size;
    information_header.width = width_;
    information_header.height = height_;

    f.write(reinterpret_cast<char*>(&file_header), sizeof(file_header));
    f.write(reinterpret_cast<char*>(&information_header), sizeof(information_header));

    for (int x = 0; x < height_; ++x) {
        for (int y = 0; y < width_; ++y) {
            unsigned char r = static_cast<unsigned char>(GetColor(x, y).r * base_values::NUM);
            unsigned char g = static_cast<unsigned char>(GetColor(x, y).g * base_values::NUM);
            unsigned char b = static_cast<unsigned char>(GetColor(x, y).b * base_values::NUM);
            unsigned char color[] = {b, r, g};
            f.write(reinterpret_cast<char*>(color), 3);
        }
        f.write(reinterpret_cast<char*>(bmp_pad), padding);
    }
    f.close();
};

