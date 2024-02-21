#include "KeyNotFoundError.h"

const char* KeyNotFoundError::what() const noexcept{
    return "Key not found in database\n";
}

const std::wstring KeyNotFoundError::wwhat() const noexcept
{
    return L"Key not found in database\n";
}
