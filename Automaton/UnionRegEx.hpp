#pragma once
#include "RegEx.hpp"

class UnionRegEx : public RegEx
{
public:
	UnionRegEx(const RegEx& lhs, const RegEx& rhs);
	UnionRegEx(const UnionRegEx& other);
	UnionRegEx& operator=(const UnionRegEx& other);
	virtual ~UnionRegEx();
	std::string toString() const override;
	Automaton toAutomaton() const override;
	bool eval(const std::string& word) const override;
	RegEx* clone() const override;

private:
	RegEx* lhs;
	RegEx* rhs;
	void free();
};