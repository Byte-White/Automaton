#include "LiteralRegEx.hpp"

LiteralRegEx::LiteralRegEx(const std::string& word) : m_word(word) {}

bool LiteralRegEx::eval(const std::string& word) const
{
	return m_word == word;
}

RegEx* LiteralRegEx::clone() const
{
	return new LiteralRegEx(*this);
}
