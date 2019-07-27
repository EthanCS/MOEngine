#pragma once

#include "Common/Util.h"

class ExceptionHandler
{
public:
	ExceptionHandler() = default;
	ExceptionHandler(HRESULT hr, const std::wstring& functionName, const std::wstring& filename, int lineNumber);

	std::wstring ToString() const;

	HRESULT ErrorCode = S_OK;
	std::wstring FunctionName;
	std::wstring Filename;
	int LineNumber = -1;
};

#ifndef ThrowIfFailed
#define ThrowIfFailed(x)                                              \
{                                                                     \
    HRESULT hr__ = (x);                                               \
    std::wstring wfn = Util::AnsiToWString(__FILE__);                       \
    if(FAILED(hr__)) { throw ExceptionHandler(hr__, L#x, wfn, __LINE__); } \
}
#endif