#pragma once
#include "../image_creation/image.h"
#include "../filters/general_filter/filter.h"
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
    virtual std::unique_ptr<BaseFilter> Create(const FilterParameters& params) const {
        return nullptr;
    };
    virtual ~FilterFactory() = default;
};

struct MatrixFilterFactory : FilterFactory {
    std::unique_ptr<BaseFilter> Create(const FilterParameters& params) const override {
        return nullptr;
    };
    virtual std::unique_ptr<FilterWithMatrix> CreateMatrix(const FilterParameters& params) const = 0;
};

struct CropFactory : public FilterFactory {
    std::unique_ptr<BaseFilter> Create(const FilterParameters& params) const override;
};

struct NegativeFactory : public FilterFactory {
    std::unique_ptr<BaseFilter> Create(const FilterParameters& params) const override;
};

struct GreyscaleFactory : public FilterFactory {
    std::unique_ptr<BaseFilter> Create(const FilterParameters& params) const override;
};

struct SharpFactory : public MatrixFilterFactory {
    std::unique_ptr<FilterWithMatrix> CreateMatrix(const FilterParameters& params) const override;
    std::unique_ptr<BaseFilter> Create(const FilterParameters& params) const override;
};

struct EdgesFactory : public MatrixFilterFactory {
    std::unique_ptr<FilterWithMatrix> CreateMatrix(const FilterParameters& params) const override;
    std::unique_ptr<BaseFilter> Create(const FilterParameters& params) const override;
};

struct BlurFactory : public FilterFactory {
    std::unique_ptr<BaseFilter> Create(const FilterParameters& params) const override;
};

struct GlassFactory : public FilterFactory {
    std::unique_ptr<BaseFilter> Create(const FilterParameters& params) const override;
};

std::vector<FilterArgs> Parser(int argc, char* argv[]);
Image Filters(Image image, std::vector<FilterArgs> filters);