#include "base.h"

int main(int argc, char* argv[]) {
    Args args;
    if (argc < 2) {
        throw ParserException("Tou haven't entered input or output file name");
    }
    args.input_file = argv[1];
    args.output_file = argv[2];
    if (argc == 2) {
        std::cout << "You should enter filters' names and arguments";
    }
    Image image = Read(args.input_file);
    std::vector<FilterArgs> filters = Parser(argc, argv);
    image = Filters(image, filters);
    Write(image, args.output_file);
    return 0;
}
