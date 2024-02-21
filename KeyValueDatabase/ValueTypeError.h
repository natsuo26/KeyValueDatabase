#pragma once
#include<exception>
#include<string>
class ValueTypeError : public std::exception {
public:
    const char* what() const noexcept override;
    const std::wstring wwhat() const noexcept;
};