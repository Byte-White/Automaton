#include "UnionRegEx.hpp"


UnionRegEx::UnionRegEx(const RegEx& lhs, const RegEx& rhs) : BinaryOperationRegEx(lhs, rhs) {}

UnionRegEx::UnionRegEx(RegEx* lhs, RegEx* rhs) : BinaryOperationRegEx(lhs, rhs) {}

std::string UnionRegEx::toString() const
{
	return "(" + lhs->toString() + "+" + rhs->toString() + ")";
}

Automaton UnionRegEx::toAutomaton() const
{
	return Union(lhs->toAutomaton(),rhs->toAutomaton());
}

bool UnionRegEx::eval(const std::string& word) const
{
	return lhs->eval(word) || rhs->eval(word);
}

RegEx* UnionRegEx::clone() const
{
	return new UnionRegEx(lhs->clone(), rhs->clone());
}

