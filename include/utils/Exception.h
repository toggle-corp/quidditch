#pragma once

class Exception : public std::exception {
public:
    Exception(const std::string& message) : mMessage(message) {}

    const char* what() const noexcept {
        return mMessage.c_str();
    }

private:
    std::string mMessage;
};