#pragma once

#include<exception>
#include <string>
#define WCHAR wchar_t
const int MaxMsgLength = 94;

class SystemError :public std::runtime_error {
public:
	SystemError(const std::wstring& msg) : runtime_error("error!"), message(msg) {};
	~SystemError() {};
	std::wstring get_message() const { return message; }

private:
	std::wstring message;
};

inline std::wstring GetErrorMessageInContextWithErrorNumber()
{
	WCHAR errMsg[MaxMsgLength];
	_wcserror_s(errMsg, MaxMsgLength, errno);
	return errMsg;
}

