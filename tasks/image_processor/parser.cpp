#include "image.h"
#include "filter.h"
#include <memory>

using FilterParameters = std::vector<std::string>;  //всё-таки удобнее string, кажется


struct FilterArgs {
    std::string name;
    FilterParameters parameters;
};

struct Args{
    std::string input_file;
    std::string output_file;
    std::vector<FilterArgs> filters; //удобнее, когда анализируем и выкидываем неподходящее уже потом
};

struct FilterFactory {
    virtual std::unique_ptr<BaseFilter> Create(const FilterParameters& params) const{};
    virtual std::unique_ptr<FilterWithMatrix> CreateMatrix(const FilterParameters& params) const{};
    virtual std::string GetHelpMessage() const{};
    virtual ~FilterFactory() = default;
};

struct CropFactory : public FilterFactory {
    std::unique_ptr<BaseFilter> Create(const FilterParameters& params) const override {
        if (params.size() != 2) {
            //ошибка, return
        }
        int width = std::stoi(params.at(0));
        int height = std::stoi(params.at(1));
        auto x = std::make_unique<Crop>(width, height);
        return x;
    }
};

struct NegativeFactory : public FilterFactory {
    std::unique_ptr<BaseFilter> Create(const FilterParameters& params) const override {
        if (!params.empty()) {
            //ошибка, return
        }
        return std::make_unique<Negative>();
    }
};

struct GreyscaleFactory : public FilterFactory {
    std::unique_ptr<BaseFilter> Create(const FilterParameters& params) const override {
        if (!params.empty()) {
            //ошибка, return
        }
        return std::make_unique<Greyscale>();
    }
};

struct SharpFactory : public FilterFactory {
    std::unique_ptr<FilterWithMatrix> CreateMatrix(const FilterParameters& params) const override {
        if (!params.empty()) {
            //ошибка, return
        }
        return std::make_unique<Sharp>();
    }
};

struct EdgesFactory : public FilterFactory {
    std::unique_ptr<FilterWithMatrix> CreateMatrix(const FilterParameters& params) const override {
        if (params.size() != 1) {
            //ошибка, return
        }
        int threshold = std::stoi(params.at(0));
        return std::make_unique<Edges>(threshold);
    }
};

struct BlurFactory : public FilterFactory {
    std::unique_ptr<BaseFilter> Create(const FilterParameters& params) const override {
        if (params.size() != 1) {
            //ошибка, return
        }
        int sigma = std::stoi(params.at(0));
        return std::make_unique<Blur>(sigma);
    }
};


