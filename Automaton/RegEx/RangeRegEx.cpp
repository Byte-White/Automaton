#include "RangeRegEx.hpp"

RangeRegEx::RangeRegEx(char start, char end)
{
	m_start = start;
	m_end = end;
	if (m_start > m_end)
		std::swap(m_start, m_end);


}

bool RangeRegEx::eval(const std::string& word) const
{
	return word.size() == 1 && word[0] >= m_start && word[0] <= m_end;
}

std::string RangeRegEx::toString() const
{
	return  "[" + std::string(1, m_start) + "-" + std::string(1, m_end) + "]";
}

RegEx* RangeRegEx::clone() const
{
	return new RangeRegEx(*this);
}

Automaton RangeRegEx::toAutomaton() const
{
	std::vector<char> alphabet;
	for (char c = m_start; c <= m_end; c++)
		alphabet.push_back(c);
	Automaton automaton(alphabet);
	automaton.createNewState(0, true, false);
	automaton.createNewState(1, false, true);
	for (char c = m_start; c <= m_end; c++)
		automaton.addTransition(0, c, 1);
	return automaton;
}