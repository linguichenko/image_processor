#include "filter.h"
#include "image.h"

int main() {
    Image image;
    const std::string path = "../tasks/image_processor/test_script/data/flag.bmp";
    image.Read(path);
    const std::string path2 = "../tasks/image_processor/output.bmp";
    //Negative negative;
    //negative.Apply(image);
    image.Write(path2);
    return 0;
}
