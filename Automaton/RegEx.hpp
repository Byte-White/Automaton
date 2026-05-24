#pragma once
#include <string>

class RegEx
{
public:
	virtual bool eval(const std::string&) const = 0;
	virtual RegEx* clone() const = 0;
	virtual ~RegEx() = default;
};