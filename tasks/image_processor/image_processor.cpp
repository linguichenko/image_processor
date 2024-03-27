#include "filter.h"
#include "image.h"
#include "parser.cpp"

// int main() {
//     Image image;
//     const std::string path = "../tasks/image_processor/test_script/data/lenna.bmp";
//     //const std::string path = "../tasks/image_processor/photo_2024-03-26_18-09-36.bmp";
//     image.Read(path);
//     const std::string path2 = "../tasks/image_processor/output.bmp";
//     Blur blur(10);
//     blur.Apply(image);
//     image.Write(path2);
//     return 0;
// }

int main(int argc, char* argv[]) {
    Args args;
    args.input_file = argv[1];
    args.output_file = argv[2];
    Image image;
    image.Read(args.input_file);
    std::vector<FilterArgs> filters;
    std::cout<<argc<<std::endl;
    int i = 3;
    int k = 0;
    while (i < argc) {
        std::cout <<"i: "<<i<<std::endl;
        if (argv[i][0] == '-') {
            FilterArgs new_args;
            new_args.name = argv[i];
            filters.push_back(new_args);
            int j = i + 1;
            while (j < argc && argv[j][0] != '-') {
                std::cout<<"j "<<j<<std::endl;
                filters[k].parameters.push_back(argv[j]);
                ++j;
            }
            i = j;
            ++k;
        }
    }
    std::cout << "something" << std::endl;
    for (FilterArgs const& arg : filters) {
        if (arg.name == "-gs") {
            GreyscaleFactory factory;
            std::unique_ptr<BaseFilter> ptr = factory.Create(arg.parameters);
            ptr->Apply(image);
        }
        if (arg.name == "-crop") {
            CropFactory factory;
            std::unique_ptr<BaseFilter> ptr = factory.Create(arg.parameters);
            ptr->Apply(image);
        }
        if (arg.name == "-neg") {
            NegativeFactory factory;
            std::unique_ptr<BaseFilter> ptr = factory.Create(arg.parameters);
            ptr->Apply(image);
        }
        if (arg.name == "-sharp") {
            SharpFactory factory;
            std::unique_ptr<FilterWithMatrix> ptr = factory.CreateMatrix(arg.parameters);
            ptr->ApplySpecial(image);
        }
        if (arg.name == "-edge") {
            std::cout<<1<<std::endl;
            EdgesFactory factory;
            std::unique_ptr<FilterWithMatrix> ptr = factory.CreateMatrix(arg.parameters);
            ptr->ApplySpecial(image);
            std::cout<<2<<std::endl;
        }
        if (arg.name == "-blur") {
            BlurFactory factory;
            std::unique_ptr<BaseFilter> ptr = factory.Create(arg.parameters);
            ptr->Apply(image);
        }
    }
    image.Write(args.output_file);
    return 0;
}
