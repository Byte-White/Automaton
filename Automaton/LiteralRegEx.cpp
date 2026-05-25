#include "LiteralRegEx.hpp"

LiteralRegEx::LiteralRegEx(const std::string& word) : m_word(word) {}

bool LiteralRegEx::eval(const std::string& word) const
{
	return m_word == word;
}

std::string LiteralRegEx::toString() const
{
	return m_word;
}

Automaton LiteralRegEx::toAutomaton() const
{
	std::vector<char> alphabet;
	for (char c : m_word)
		if (std::find(alphabet.begin(), alphabet.end(), c) == alphabet.end())
			alphabet.push_back(c);

	Automaton automaton(alphabet);
	size_t id = 0;
	
	for (size_t i = 0; i <= m_word.size(); i++)
		automaton.createNewState(i, i == 0, i == m_word.size());

	for (char c : m_word)
	{
		automaton.addTransition(id, c, id + 1);
		id++;
	}

	return automaton;
}

RegEx* LiteralRegEx::clone() const
{
	return new LiteralRegEx(*this);
}
