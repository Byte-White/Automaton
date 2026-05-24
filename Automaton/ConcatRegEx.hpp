#pragma once
#include "RegEx.hpp"

class ConcatRegEx : public RegEx
{
public:
	ConcatRegEx(const RegEx& lhs, const RegEx& rhs) : lhs(lhs.clone()), rhs(rhs.clone()) {}
	ConcatRegEx(const ConcatRegEx& other) : lhs(other.lhs->clone()), rhs(other.rhs->clone()) {}
	ConcatRegEx& operator=(const ConcatRegEx& other)
	{
		if (this != &other)
		{
			free();
			lhs = other.lhs->clone();
			rhs = other.rhs->clone();
		}
		return *this;
	}
	virtual ~ConcatRegEx()
	{
		free();
	}

	bool eval(const std::string& word) const override
	{
		for(int i = 0; i <= word.size(); i++)
			if (lhs->eval(word.substr(0, i)) && rhs->eval(word.substr(i)))
				return true;
		return false;
	}
	RegEx* clone() const override
	{
		return new ConcatRegEx(*lhs, *rhs);
	}

private:
	RegEx* lhs;
	RegEx* rhs;
	void free()
	{
		delete lhs;
		delete rhs;
	}
};