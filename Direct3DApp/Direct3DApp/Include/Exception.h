#pragma once
#include<exception>
#include<string>

class Exception : public std::exception
{
public:
	Exception(int pLine, const char* pFile) noexcept;
	const char* what() const noexcept override;
	virtual inline const char* GetType() const noexcept { return "Exception"; };
	inline int GetLine() const noexcept { return this->Line; };
	inline const std::string& GetFile() const noexcept { return this->File; };
	std::string GetOriginString() const noexcept;
private:
	int Line;
	std::string File;
protected:
	mutable std::string WhatBuffer;
};