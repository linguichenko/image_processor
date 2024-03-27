#include "filter.h"
#include "image.h"
#include "parser.cpp"

// int main() {
//     Image image;
//     const std::string path = "../tasks/image_processor/test_script/data/lenna.bmp";
//     //const std::string path = "../tasks/image_processor/photo_2024-03-26_18-09-36.bmp";
//     image.Read(path);
//     const std::string path2 = "../tasks/image_processor/output.bmp";
//     Edges edges(0.1);
//     edges.Apply(image);
//     image.Write(path2);
//     return 0;
// }

int main(int argc, char* argv[]) {
    Args args;
    args.input_file = argv[0];
    args.output_file = argv[1];
    Image image;
    image.Read(args.input_file);
    std::vector<FilterArgs> filters(argc - 1);
    int i = 2;
    while (i < argc) {
        if (argv[i][0] == '-') {
            FilterArgs new_args;
            new_args.name = argv[i];
            filters.push_back(new_args);
            int j = i + 1;
            while (argv[j][0] != '-') {
                filters[i].parameters.push_back(argv[i]);
            }
            i = j;
        }
    }
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
            std::unique_ptr<BaseFilter> ptr = factory.Create(arg.parameters);
            ptr->Apply(image);
        }
        if (arg.name == "-edge") {
            EdgesFactory factory;
            std::unique_ptr<BaseFilter> ptr = factory.Create(arg.parameters);
            ptr->Apply(image);
        }
        if (arg.name == "-blur") {
            BlurFactory factory;
            std::unique_ptr<BaseFilter> ptr = factory.Create(arg.parameters);
            ptr->Apply(image);
        }
    }
    image.Write(args.output_file);
}
