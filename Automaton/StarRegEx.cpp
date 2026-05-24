#include "StarRegEx.hpp"

StarRegEx::StarRegEx(const RegEx& inner) : inner(inner.clone()) {}

StarRegEx::StarRegEx(const StarRegEx& other) : inner(other.inner->clone()) {}

StarRegEx& StarRegEx::operator=(const StarRegEx& other)
{
	if (this != &other)
	{
		free();
		inner = other.inner->clone();
	}
	return *this;
}

StarRegEx::~StarRegEx()
{
	free();
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

RegEx* StarRegEx::clone() const
{
	return new StarRegEx(*inner);
}

void StarRegEx::free()
{
	delete inner;
}
