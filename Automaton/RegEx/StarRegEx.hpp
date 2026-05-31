#pragma once
#include "RegEx.hpp"


/**
* @brief Класът StarRegEx представлява регулярни изрази, които са звезда на друг регулярен израз.
**/
class StarRegEx : public RegEx
{
public:

	/**
	* @brief Конструктор, който приема друг регулярен израз и създава звезда на този израз.
	**/
	StarRegEx(const RegEx& inner);
	StarRegEx(const StarRegEx& other);
	StarRegEx& operator=(const StarRegEx& other);
	virtual ~StarRegEx();
	bool eval(const std::string& word) const override;
	Automaton toAutomaton() const override;
	std::string toString() const override;
	RegEx* clone() const override;
private:
	RegEx* inner;
	void free();
};