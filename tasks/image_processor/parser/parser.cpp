#include "../base.h"

std::unique_ptr<BaseFilter> CropFactory::Create(const FilterParameters& params) const {
    if (params.size() != 2) {
        //ошибка, return
    }
    int width = std::stoi(params.at(0));
    int height = std::stoi(params.at(1));
    return std::make_unique<Crop>(width, height);
}
std::unique_ptr<FilterWithMatrix> CropFactory::CreateMatrix(const FilterParameters& params) const {
    return nullptr;
}

std::unique_ptr<BaseFilter> NegativeFactory::Create(const FilterParameters& params) const {
    if (!params.empty()) {
        //ошибка, return
    }
    return std::make_unique<Negative>();
}
std::unique_ptr<FilterWithMatrix> NegativeFactory::CreateMatrix(const FilterParameters& params) const {
    return nullptr;
}

std::unique_ptr<BaseFilter> GreyscaleFactory::Create(const FilterParameters& params) const {
    if (!params.empty()) {
        //ошибка, return
    }
    return std::make_unique<Greyscale>();
}
std::unique_ptr<FilterWithMatrix> GreyscaleFactory::CreateMatrix(const FilterParameters& params) const {
    return nullptr;
}

std::unique_ptr<FilterWithMatrix> SharpFactory::CreateMatrix(const FilterParameters& params) const {
    if (!params.empty()) {
        //ошибка, return
    }
    return std::make_unique<Sharp>();
}
std::unique_ptr<BaseFilter> SharpFactory::Create(const FilterParameters& params) const {
    return nullptr;
}

std::unique_ptr<FilterWithMatrix> EdgesFactory::CreateMatrix(const FilterParameters& params) const {
    if (params.size() != 1) {
        //ошибка, return
    }
    float threshold = std::stof(params.at(0));
    return std::make_unique<Edges>(threshold);
}
std::unique_ptr<BaseFilter> EdgesFactory::Create(const FilterParameters& params) const {
    return nullptr;
}

std::unique_ptr<BaseFilter> BlurFactory::Create(const FilterParameters& params) const {
    if (params.size() != 1) {
        //ошибка, return
    }
    float sigma = std::stof(params.at(0));
    return std::make_unique<Blur>(sigma);
}
std::unique_ptr<FilterWithMatrix> BlurFactory::CreateMatrix(const FilterParameters& params) const {
    return nullptr;
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
            EdgesFactory factory;
            std::unique_ptr<FilterWithMatrix> ptr = factory.CreateMatrix(arg.parameters);
            ptr->ApplySpecial(image);
        }
        if (arg.name == "-blur") {
            BlurFactory factory;
            std::unique_ptr<BaseFilter> ptr = factory.Create(arg.parameters);
            ptr->Apply(image);
        }
    }
    return image;
}
