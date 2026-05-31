#include "ConcatRegEx.hpp"

ConcatRegEx::ConcatRegEx(const RegEx& lhs, const RegEx& rhs) : lhs(lhs.clone()), rhs(rhs.clone()) {}

ConcatRegEx::ConcatRegEx(const ConcatRegEx& other) : lhs(other.lhs->clone()), rhs(other.rhs->clone()) {}

ConcatRegEx& ConcatRegEx::operator=(const ConcatRegEx& other)
{
	if (this != &other)
	{
		free();
		lhs = other.lhs->clone();
		rhs = other.rhs->clone();
	}
	return *this;
}

ConcatRegEx::~ConcatRegEx()
{
	free();
}

std::string ConcatRegEx::toString() const
{
	return "(" + lhs->toString() + rhs->toString() + ")";
}

Automaton ConcatRegEx::toAutomaton() const
{
	return Concat(lhs->toAutomaton(),rhs->toAutomaton());
}

bool ConcatRegEx::eval(const std::string& word) const
{
	for (int i = 0; i <= word.size(); i++)
		if (lhs->eval(word.substr(0, i)) && rhs->eval(word.substr(i)))
			return true;
	return false;
}

RegEx* ConcatRegEx::clone() const
{
	return new ConcatRegEx(*lhs, *rhs);
}

void ConcatRegEx::free()
{
	delete lhs;
	delete rhs;
}
