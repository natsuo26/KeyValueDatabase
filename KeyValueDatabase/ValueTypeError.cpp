#include "ValueTypeError.h"

const char* ValueTypeError::what() const noexcept
{
    return "Value type error\n";
}

const std::wstring ValueTypeError::wwhat() const noexcept
{
    return L"Value type error\n";
}
