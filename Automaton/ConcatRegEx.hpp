#pragma once
#include "RegEx.hpp"

class ConcatRegEx : public RegEx
{
public:
	ConcatRegEx(const RegEx& lhs, const RegEx& rhs);
	ConcatRegEx(const ConcatRegEx& other);
	ConcatRegEx& operator=(const ConcatRegEx& other);
	virtual ~ConcatRegEx();

	std::string toString() const override;
	Automaton toAutomaton() const override;
	bool eval(const std::string& word) const override;
	RegEx* clone() const override;

private:
	RegEx* lhs;
	RegEx* rhs;
	void free();
};