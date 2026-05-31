#pragma once
#include "RegEx.hpp"


/**
* @brief Класът LiteralRegEx представлява регулярни изрази, които съответстват на конкретна дума.
**/
class LiteralRegEx : public RegEx
{
public:

	/**
	* @brief Конструктор, който приема дума и създава регулярен израз.
	**/
	LiteralRegEx(const std::string& word);

	bool eval(const std::string& word) const override;

	std::string toString() const override;

	Automaton toAutomaton() const override;

	RegEx* clone() const override;
private:
	std::string m_word;
};