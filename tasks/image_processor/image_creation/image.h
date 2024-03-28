#pragma once
#include <cstdint>
#include <vector>
#include <iostream>
#include <fstream>

namespace base_values {
const uint16_t FILE_TYPE{19778};
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
};  // namespace base_values

#pragma pack(push, 1)
struct FileHeader {
    uint16_t file_type{base_values::FILE_TYPE};
    uint32_t file_size{base_values::FILE_SIZE};
    uint32_t unused{base_values::UNUSED};
    int32_t offset_data{base_values::OFFSET_DATA};
};
#pragma pack(pop)

#pragma pack(push, 1)
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
#pragma pack(pop)  // не получилось без прагмы, почему-то не работало отдельное считывание(

struct Color {
    float r, g, b;
    Color();
    Color(float r, float g, float b);
    ~Color(){};
};

class Image {
private:
    int width_;
    int height_;
public:
    Image(){};
    Image(int width, int height);

    ~Image(){};

    Color GetColor(int x, int y) const;

    void SetColor(float r, float g, float b, int x, int y);

    void SetWidth(int width);

    void SetHeight(int height);

    void SetColors(std::vector<std::vector<Color>> new_pixels);

    int GetWidth() const;
    int GetHeight() const;

    std::vector<std::vector<Color>> colors_;
};

Image Read(const std::string path);

void Write(const Image &image, const std::string path);