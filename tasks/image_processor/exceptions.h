#pragma once
#include "exception"
#include <string>

class ImageProcessorException : public std::exception {
protected:
    std::string message;

public:
    explicit ImageProcessorException(const std::string text) : message(text) {
    }
    const char* what() const noexcept override = 0;
};

class OtherException : public ImageProcessorException {
public:
    explicit OtherException(const std::string& message)
        : ImageProcessorException("Other exception with message: " + message) {
    }
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class ReadImageException : public ImageProcessorException {
public:
    explicit ReadImageException(const std::string& message)
        : ImageProcessorException("ReadImage exception with message: " + message) {
    }
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class FilterException : public ImageProcessorException {
public:
    explicit FilterException(const std::string& message)
        : ImageProcessorException("Filter exception with message: " + message) {
    }
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class ParserException : public ImageProcessorException {
public:
    explicit ParserException(const std::string& message)
        : ImageProcessorException("Parser exception with message: " + message) {
    }
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class WriteImageException : public ImageProcessorException {
public:
    explicit WriteImageException(const std::string& message)
        : ImageProcessorException("WriteImage exception with message: " + message) {
    }
    const char* what() const noexcept override {
        return message.c_str();
    }
};
