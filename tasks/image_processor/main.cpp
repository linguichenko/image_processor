#include "filter.h"
#include "image.h"

int main() {
    Image image;
    const std::string path = "../tasks/image_processor/test_script/data/lenna.bmp";
    image.Read(path);
    const std::string path2 = "../tasks/image_processor/output.bmp";
    /*Edges edges(0.1);
    edges.Apply(image);*/
//    for (int i = 0; i < image.height_; ++i) {
//        for (int j = 0; j < image.width_; ++j) {
//            image.SetColor(1, 1, 1, i, j);
//       }
    //  }
    Sharp sharp;
    sharp.Apply(image);
    image.Write(path2);
    return 0;
}
