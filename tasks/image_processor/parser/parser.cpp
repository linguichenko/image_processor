#include <map>
#include "../base.h"

std::unique_ptr<BaseFilter> CropFactory::Create(const FilterParameters& params) const {
    if (params.size() != 2) {
        throw FilterException("incorrect number of arguments");
    }
    int width = std::stoi(params.at(0));
    int height = std::stoi(params.at(1));
    return std::make_unique<Crop>(width, height);
}

std::unique_ptr<BaseFilter> NegativeFactory::Create(const FilterParameters& params) const {
    if (!params.empty()) {
        throw FilterException("incorrect number of arguments");
    }
    return std::make_unique<Negative>();
}

std::unique_ptr<BaseFilter> GreyscaleFactory::Create(const FilterParameters& params) const {
    if (!params.empty()) {
        throw FilterException("incorrect number of arguments");
    }
    return std::make_unique<Greyscale>();
}

std::unique_ptr<FilterWithMatrix> SharpFactory::CreateMatrix(const FilterParameters& params) const {
    if (!params.empty()) {
        throw FilterException("incorrect number of arguments");
    }
    return std::make_unique<Sharp>();
}
std::unique_ptr<BaseFilter> SharpFactory::Create(const FilterParameters& params) const {
    return nullptr;
}

std::unique_ptr<FilterWithMatrix> EdgesFactory::CreateMatrix(const FilterParameters& params) const {
    if (params.size() != 1) {
        throw FilterException("incorrect number of arguments");
    }
    float threshold = std::stof(params.at(0));
    return std::make_unique<Edges>(threshold);
}
std::unique_ptr<BaseFilter> EdgesFactory::Create(const FilterParameters& params) const {
    return nullptr;
}

std::unique_ptr<BaseFilter> BlurFactory::Create(const FilterParameters& params) const {
    if (params.size() != 1) {
        throw FilterException("incorrect number of arguments");
    }
    float sigma = std::stof(params.at(0));
    return std::make_unique<Blur>(sigma);
}

std::unique_ptr<BaseFilter> GlassFactory::Create(const FilterParameters& params) const {
    if (params.size() != 1) {
        throw FilterException("incorrect number of arguments");
    }
    float cell_size = std::stof(params.at(0));
    return std::make_unique<Glass>(cell_size);
}

std::vector<FilterArgs> Parser(int argc, char* argv[]) {
    std::vector<FilterArgs> filters;
    int i = 3;
    int k = 0;
    while (i < argc) {
        if (argv[i][0] == '-') {
            FilterArgs new_args;
            new_args.name = argv[i];
            filters.push_back(new_args);
            int j = i + 1;
            while (j < argc && argv[j][0] != '-') {
                filters[k].parameters.push_back(argv[j]);
                ++j;
            }
            i = j;
            ++k;
        }
    }
    return filters;
}

Image Filters(Image image, std::vector<FilterArgs> filters) {
    GreyscaleFactory greyscale;
    CropFactory crop;
    NegativeFactory negative;
    GlassFactory glass;
    SharpFactory sharp;
    BlurFactory blur;
    EdgesFactory edges;
    std::map<std::string, FilterFactory*> filters_map = {
        {"-gs", &greyscale}, {"-crop", &crop}, {"-neg", &negative}, {"-blur", &blur}, {"-glass", &glass}};
    std::map<std::string, MatrixFilterFactory*> matrix_filters_map = {{"-sharp", &sharp}, {"-edge", &edges}};
    for (FilterArgs const& arg : filters) {
        if (!filters_map.contains(arg.name) && !matrix_filters_map.contains(arg.name)) {
            throw FilterException("filter does not exist");
        }
        if (filters_map.contains(arg.name)) {
            std::unique_ptr<BaseFilter> ptr = filters_map.at(arg.name)->Create(arg.parameters);
            ptr->Apply(image);
        } else {
            std::unique_ptr<FilterWithMatrix> ptr = matrix_filters_map.at(arg.name)->CreateMatrix(arg.parameters);
            ptr->Apply(image);
        }
    }
    return image;
}
