#include <vector>
#include <iostream>
#include <fstream>

struct Color {
    float r, g, b;

    Color() : r(0), g(0), b(0) {};
    Color(float r, float g, float b) : r(r), g(r), b(r) {};
    ~Color() {};
};

class Image {
private:
    int width_;
    int heigth_;
    std::vector<Color> colors_;
public:
    Image(int width, int heigth) : width_(width), heigth_(heigth), colors_(std::vector<Color>(width * heigth)){};
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
        const size_t char_size = sizeof(char);
        f.open(path, std::ios::in | std::ios::binary);

        const int file_header_size = 14;
        const int information_header_size = 40;

        unsigned char file_header[file_header_size];
        f.read(reinterpret_cast<char*>(file_header), file_header_size);

        if (file_header[0] != 'B' || file_header[1] != 'M') {
            //ошибка
            f.close();
            return;
        }

        unsigned char information_header[information_header_size];
        f.read(reinterpret_cast<char*>(information_header), information_header_size);

        width_ = information_header[4] + (information_header[5] << char_size)
                 + (information_header[6] << 2 * char_size) + (information_header[7] << 3 * char_size);
        heigth_ = information_header[8] + (information_header[9] << char_size)
                  + (information_header[10] << 2 * char_size) + (information_header[11] << 3 * char_size);

        colors_.resize(width_ * heigth_);
        const int padding = ((4 - width_ * 3 % 4) % 4);

        for (int y = 0; y < heigth_; ++y) {
            for (int x = 0; x < width_; ++x) {
                unsigned char color[3];
                f.read(reinterpret_cast<char*>(color), 3);

                colors_[y * width_ + x].r = static_cast<float>(color[2]) / 255.0f;
                colors_[y * width_ + x].g = static_cast<float>(color[1]) / 255.0f;
                colors_[y * width_ + x].b = static_cast<float>(color[0]) / 255.0f;
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
        const int file_size = file_header_size + information_header_size + width_ * heigth_ * 3 + padding * heigth_;
        const size_t char_size = sizeof(char);

        unsigned char file_header[file_header_size];
        for (size_t i = 0; i < file_header_size; ++i) {
            file_header[i] = 0;
        }
        file_header[0] = 'B';
        file_header[1] = 'M';
        file_header[2] = file_size;
        file_header[3] = file_size >> char_size;
        file_header[4] = file_size >> 2 * char_size;
        file_header[5] = file_size >> 3 * char_size;
        file_header[10] = file_header_size + information_header_size;

        unsigned char information_header[information_header_size];
        for (size_t i = 0; i < information_header_size; ++i) {
            information_header[i] = 0;
        }
        information_header[0] = information_header_size;
        information_header[4] = width_;
        information_header[5] = width_ >> char_size;
        information_header[6] = width_ >> 2 * char_size;
        information_header[7] = width_ >> 3 * char_size;
        information_header[8] = heigth_;
        information_header[9] = heigth_ >> char_size;
        information_header[10] = heigth_ >> 2 * char_size;
        information_header[11] = heigth_ >> 3 * char_size;
        information_header[12] = 1;
        information_header[14] = 24;

        f.write(reinterpret_cast<char*>(file_header), file_header_size);
        f.write(reinterpret_cast<char*>(information_header), information_header_size);

        for (int y = 0; y < heigth_; ++y) {
            for (int x = 0; x < width_; ++x) {
                unsigned char r = static_cast<unsigned char>(GetColor(x, y).r * 255.0f);
                unsigned char g = static_cast<unsigned char>(GetColor(x, y).g * 255.0f);
                unsigned char b = static_cast<unsigned char>(GetColor(x, y).b * 255.0f);

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
