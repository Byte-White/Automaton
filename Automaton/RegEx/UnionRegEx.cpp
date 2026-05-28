#include "UnionRegEx.hpp"

UnionRegEx::UnionRegEx(const RegEx& lhs, const RegEx& rhs) : lhs(lhs.clone()), rhs(rhs.clone()) {}

UnionRegEx::UnionRegEx(const UnionRegEx& other) : lhs(other.lhs->clone()), rhs(other.rhs->clone()) {}

UnionRegEx& UnionRegEx::operator=(const UnionRegEx& other)
{
	if (this != &other)
	{
		free();
		lhs = other.lhs->clone();
		rhs = other.rhs->clone();
	}
	return *this;
}

UnionRegEx::~UnionRegEx()
{
	free();
}

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
	return new UnionRegEx(*lhs, *rhs);
}

void UnionRegEx::free()
{
	delete lhs;
	delete rhs;
}
