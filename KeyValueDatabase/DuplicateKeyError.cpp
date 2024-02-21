#include "DuplicateKeyError.h"

const char* DuplicateKeyError::what() const noexcept
{
    return "Duplicate key found in database\n";
}

const wchar_t* DuplicateKeyError::wwhat() const noexcept
{
    return L"Duplicate key found in database\n";
}