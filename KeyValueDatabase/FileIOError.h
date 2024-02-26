#pragma once
#include<exception>
#include<string>
class FileIOError : public std::exception {
public:
    const char* what() const noexcept override;
    const std::wstring wwhat() const noexcept;
};
