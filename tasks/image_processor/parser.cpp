#include "image.h"
#include "filter.h"
#include <memory>

using FilterParameters = std::vector<std::string>;

struct FilterArgs {
    std::string name;
    FilterParameters parameters;
};

struct Args {
    std::string input_file;
    std::string output_file;
    std::vector<FilterArgs> filters;
};

struct FilterFactory {
    virtual std::unique_ptr<BaseFilter> Create(const FilterParameters& params) const = 0;
    virtual std::unique_ptr<FilterWithMatrix> CreateMatrix(const FilterParameters& params) const = 0;
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
    std::unique_ptr<FilterWithMatrix> CreateMatrix(const FilterParameters& params) const override {
        return nullptr;
    }
};

struct NegativeFactory : public FilterFactory {
    std::unique_ptr<BaseFilter> Create(const FilterParameters& params) const override {
        if (!params.empty()) {
            //ошибка, return
        }
        return std::make_unique<Negative>();
    }
    std::unique_ptr<FilterWithMatrix> CreateMatrix(const FilterParameters& params) const override {
        return nullptr;
    }
};

struct GreyscaleFactory : public FilterFactory {
    std::unique_ptr<BaseFilter> Create(const FilterParameters& params) const override {
        if (!params.empty()) {
            //ошибка, return
        }
        return std::make_unique<Greyscale>();
    }
    std::unique_ptr<FilterWithMatrix> CreateMatrix(const FilterParameters& params) const override {
        return nullptr;
    }
};

struct SharpFactory : public FilterFactory {
    std::unique_ptr<FilterWithMatrix> CreateMatrix(const FilterParameters& params) const override {
        if (!params.empty()) {
            //ошибка, return
        }
        return std::make_unique<Sharp>();
    }
    std::unique_ptr<BaseFilter> Create(const FilterParameters& params) const override {
        return nullptr;
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
    std::unique_ptr<BaseFilter> Create(const FilterParameters& params) const override {
        return nullptr;
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
    std::unique_ptr<FilterWithMatrix> CreateMatrix(const FilterParameters& params) const override {
        return nullptr;
    }
};


