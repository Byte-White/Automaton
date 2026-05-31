#include "StarRegEx.hpp"

StarRegEx::StarRegEx(const RegEx& inner)
{
	this->inner.reset(inner.clone());
}

StarRegEx::StarRegEx(RegEx* inner) : inner(inner) {}

StarRegEx::StarRegEx(const StarRegEx& other) : inner(other.inner->clone()) {}

StarRegEx& StarRegEx::operator=(const StarRegEx& other)
{
	if (this != &other)
	{
		inner.reset(other.inner->clone());
	}
	return *this;
}

bool StarRegEx::eval(const std::string& word) const
{
	if (word.empty())
		return true;

	for (int i = 0; i <= word.size(); i++)
		if (inner->eval(word.substr(0, i)) && eval(word.substr(i)))
			return true;

	return false;
}

Automaton StarRegEx::toAutomaton() const
{
	return Star(inner->toAutomaton());
}

std::string StarRegEx::toString() const
{
	return "(" + inner->toString() + ")*";
}

RegEx* StarRegEx::clone() const
{
	return new StarRegEx(inner->clone());
}
