#pragma once
#include "exception"
#include <string>

class Exception : public std::exception {
private:
    std::string message_;

public:
    explicit Exception(const std::string text) : message_(text) {
    }
    const char* what() const noexcept override {
        return message_.c_str();
    }
};

class ReadImageException : public std::exception {
private:
    std::string message_;

public:
    explicit ReadImageException(const std::string text) : message_(text) {
    }
    const char* what() const noexcept override {
        return message_.c_str();
    }
};

class FilterException : public std::exception {
private:
    std::string message_;

public:
    explicit FilterException(const std::string text) : message_(text) {
    }
    const char* what() const noexcept override {
        return message_.c_str();
    }
};
