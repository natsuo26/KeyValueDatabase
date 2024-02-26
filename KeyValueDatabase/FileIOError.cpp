#include "FileIOError.h"

const char* FileIOError::what() const noexcept
{
	return "File I/O error occurred\n";
}

const std::wstring FileIOError::wwhat() const noexcept
{
	return L"File I/O error occurred\n";
}
