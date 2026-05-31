#include "ConcatRegEx.hpp"


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
