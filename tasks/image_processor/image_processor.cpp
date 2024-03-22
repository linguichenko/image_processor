#include <vector>
#include <iostream>
#include <fstream>
#include <cstdint>

namespace base_values{
const uint16_t FILE_TYPE{0x4D42};
const uint32_t FILE_SIZE{0};
const uint32_t UNUSED{0};
const int32_t OFFSET_DATA{54};
const uint32_t SIZE{40};
const int32_t WIDTH{0};
const int32_t HEIGHT{0};
const uint16_t PLANES{1};
const uint16_t BIT_COUNT{24};
const uint32_t COMPRESSION{0};
const uint32_t SIZE_IMAGE{0};
const uint32_t X_PIXELS_PER_METER{0};
const uint32_t Y_PIXELS_PER_METER{0};
const uint32_t COLORS_USED{0};
const uint32_t COLORS_IMPORTANT{0};
const float NUM{255.0f};
}


struct FileHeader {
    uint16_t file_type{base_values::FILE_TYPE};
    uint32_t file_size{base_values::FILE_SIZE};
    uint32_t unused{base_values::UNUSED};
    uint32_t offset_data{base_values::OFFSET_DATA};
};

struct DIBHeader {
    uint32_t size{base_values::SIZE};
    int32_t width{base_values::WIDTH};
    int32_t height{base_values::HEIGHT};
    uint16_t planes{base_values::PLANES};
    uint16_t bit_count{base_values::BIT_COUNT};
    uint32_t compression{base_values::COMPRESSION};
    uint32_t size_image{base_values::SIZE_IMAGE};
    uint32_t x_pixels_per_meter{base_values::X_PIXELS_PER_METER};
    uint32_t y_pixels_per_meter{base_values::Y_PIXELS_PER_METER};
    uint32_t colors_used{base_values::COLORS_USED};
    uint32_t colors_important{base_values::COLORS_IMPORTANT};
};

struct Color {
    float r, g, b;
    Color() : r(0), g(0), b(0) {};
    Color(float r, float g, float b) : r(r), g(r), b(r) {};
    ~Color() {};
};

class Image {
private:
    int width_;
    int height_;
    std::vector<Color> colors_;
public:
    Image(int width, int height) : width_(width), height_(height), colors_(std::vector<Color>(width * height)){};
    ~Image();

    Color GetColor(int x, int y) const {
        return colors_[y * width_ + x];
    };

    void SetColor(const Color& color, int x, int y) {
        colors_[y * width_ + x].r = color.r;
        colors_[y * width_ + x].g = color.g;
        colors_[y * width_ + x].b = color.b;
    };

    void Read(const char* path) {
        std::ifstream f;
        f.open(path, std::ios::in | std::ios::binary);

        const int file_header_size = 14;

        FileHeader file_header;
        DIBHeader information_header;

        f.read(reinterpret_cast<char*>(&file_header), sizeof(file_header));
        f.read(reinterpret_cast<char*>(&information_header), sizeof(information_header));

        width_ = information_header.width;
        height_ = information_header.height;
        colors_.resize(width_ * height_);
        const int padding = ((4 - width_ * 3 % 4) % 4);

        for (int y = 0; y < height_; ++y) {
            for (int x = 0; x < width_; ++x) {
                unsigned char color[3];
                f.read(reinterpret_cast<char*>(color), 3);

                colors_[y * width_ + x].r = static_cast<float>(color[2]) / base_values::NUM;
                colors_[y * width_ + x].g = static_cast<float>(color[1]) / base_values::NUM;
                colors_[y * width_ + x].b = static_cast<float>(color[0]) / base_values::NUM;
            }
            f.ignore(padding);
        }
        f.close();
    };

    void Write(const char* path) const {
        std::ofstream f;
        f.open(path, std::ios::out | std::ios::binary);

        unsigned char bmp_pad[3] = {0, 0, 0};
        const int padding = ((4 - width_ * 3 % 4) % 4);

        const int file_header_size = 14;
        const int information_header_size = 40;
        const int file_size = file_header_size + information_header_size + width_ * height_ * 3 + padding * height_;
        const size_t char_size = sizeof(char);

        FileHeader file_header;
        DIBHeader information_header;

        file_header.file_size = file_size;

        file_header.file_type = base_values::FILE_TYPE;
        file_header.file_size = file_size;
        file_header.offset_data = file_header_size + information_header_size;

        information_header.size = information_header_size;
        information_header.width = width_;
        information_header.height = height_;

        f.write(reinterpret_cast<char*>(&file_header), sizeof(file_header));
        f.write(reinterpret_cast<char*>(&information_header), sizeof(information_header));

        for (int y = 0; y < height_; ++y) {
            for (int x = 0; x < width_; ++x) {
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
};



int main(int argc, char** argv) {
    return 0;
}
