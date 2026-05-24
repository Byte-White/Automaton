#pragma once
#include "RegEx.hpp"

class StarRegEx : public RegEx
{
public:
	StarRegEx(const RegEx& inner);
	StarRegEx(const StarRegEx& other);
	StarRegEx& operator=(const StarRegEx& other);
	virtual ~StarRegEx();
	bool eval(const std::string& word) const override;

	RegEx* clone() const override;
private:
	RegEx* inner;
	void free();
};