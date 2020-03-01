#include "../Include/Exception.h"
#include <sstream>

Exception::Exception(int pLine, const char* pFile) noexcept 
	: Line(pLine), File(pFile)
{

}

const char* Exception::what() const noexcept 
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< GetOriginString();
	WhatBuffer = oss.str();
	return WhatBuffer.c_str();
}

std::string Exception::GetOriginString() const noexcept
{
	std::ostringstream oss;
	oss << "[File] " << this->File << std::endl
		<< "[Line] " << this->Line;
	return oss.str();
}
