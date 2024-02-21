#pragma once
#include<exception>
#include<string>

class DuplicateKeyError : public std::exception {
public:
    const char* what() const noexcept override;
    const wchar_t* wwhat() const noexcept;
};