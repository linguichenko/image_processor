#include "image.h"
#include "../exceptions.h"

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

void Image::SetWidth(int width) {
    width_ = width;
}

void Image::SetHeight(int height) {
    height_ = height;
}

int Image::GetHeight() const {
    return height_;
}

int Image::GetWidth() const {
    return width_;
}

Image Read(const std::string path) {
    std::ifstream f{path, std::ios::in | std::ios::binary};

    FileHeader file_header;
    DIBHeader information_header;
    Image image;

    if (!f.is_open()) {
        throw ReadImageException("can't open file");
    }

    f.read(reinterpret_cast<char *>(&file_header), sizeof(file_header));
    f.read(reinterpret_cast<char *>(&information_header), sizeof(information_header));

    if (file_header.file_type != base_values::FILE_TYPE) {
        throw ReadImageException("Bad file");
    }
    if (file_header.unused != base_values::UNUSED) {
        throw ReadImageException("Bad file");
    }
    if (information_header.planes != base_values::PLANES) {
        throw ReadImageException("Bad file");
    }
    if (information_header.bit_count != base_values::BIT_COUNT) {
        throw ReadImageException("Bad file");
    }
    if (information_header.colors_important != base_values::COLORS_IMPORTANT) {
        throw ReadImageException("Bad file");
    }
    if (information_header.colors_used != base_values::COLORS_USED) {
        throw ReadImageException("Bad file");
    }
    if (information_header.compression != base_values::COMPRESSION) {
        throw ReadImageException("Bad file");
    }

    image.SetWidth(information_header.width);
    image.SetHeight(information_header.height);

    int width = image.GetWidth();
    int height = image.GetHeight();

    image.colors_.assign(height, std::vector<Color>(width));
    const int padding = ((4 - width * 3 % 4) % 4);

    f.ignore(file_header.offset_data - static_cast<int64_t>(sizeof(information_header)) -
             static_cast<int64_t>(sizeof(file_header)));
    for (int x = 0; x < height; ++x) {
        for (int y = 0; y < width; ++y) {
            unsigned char color[3];
            f.read(reinterpret_cast<char *>(color), 3);

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

    if (!f.is_open()) {
        throw Exception("can't open file");
    }

    int width = image.GetWidth();
    int height = image.GetHeight();

    unsigned char bmp_pad[3] = {0, 0, 0};
    const int padding = ((4 - width * 3 % 4) % 4);

    const int information_header_size = 40;

    FileHeader file_header;
    DIBHeader information_header;

    file_header.file_type = base_values::FILE_TYPE;
    file_header.file_size = file_header.offset_data + 3 * height * width + height * padding;

    information_header.size = information_header_size;
    information_header.width = width;
    information_header.height = height;

    f.write(reinterpret_cast<char *>(&file_header), sizeof(file_header));
    f.write(reinterpret_cast<char *>(&information_header), sizeof(information_header));

    for (int x = 0; x < height; ++x) {
        for (int y = 0; y < width; ++y) {
            unsigned char r = static_cast<unsigned char>(image.GetColor(x, y).r * base_values::NUM);
            unsigned char g = static_cast<unsigned char>(image.GetColor(x, y).g * base_values::NUM);
            unsigned char b = static_cast<unsigned char>(image.GetColor(x, y).b * base_values::NUM);
            unsigned char color[] = {b, g, r};
            f.write(reinterpret_cast<char *>(color), 3);
        }
        f.write(reinterpret_cast<char *>(bmp_pad), padding);
    }
    f.close();
};
