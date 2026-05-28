#pragma once
#include "RegEx.hpp"

class LiteralRegEx : public RegEx
{
public:
	LiteralRegEx(const std::string& word);
	bool eval(const std::string& word) const override;
	std::string toString() const override;
	Automaton toAutomaton() const override;
	RegEx* clone() const override;
private:
	std::string m_word;
};