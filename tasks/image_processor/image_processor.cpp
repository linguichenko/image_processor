#include "image_creation/image.h"
#include "parser/parser.cpp"

int main(int argc, char* argv[]) {
    Args args;
    args.input_file = argv[1];
    args.output_file = argv[2];
    Image image = Read(args.input_file);
    std::vector<FilterArgs> filters = Parser(args, argc, argv);
    image = Filters(image, filters);
    Write(image, args.output_file);
    return 0;
}
