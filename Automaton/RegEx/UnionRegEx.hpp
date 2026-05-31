#pragma once
#include "RegEx.hpp"


/**
* @brief Класът UnionRegEx представлява обединение на два други регулярни израза.
**/
class UnionRegEx : public RegEx
{
public:

	/**
	* @param lhs Левият израз на обединението, който е указател към обект от тип RegEx.
	* @param rhs Десният израз на обединението, който е указател към обект от тип RegEx.
	**/
	UnionRegEx(const RegEx& lhs, const RegEx& rhs);
	UnionRegEx(const UnionRegEx& other);
	UnionRegEx& operator=(const UnionRegEx& other);
	virtual ~UnionRegEx();
	std::string toString() const override;
	Automaton toAutomaton() const override;
	bool eval(const std::string& word) const override;
	RegEx* clone() const override;

private:
	RegEx* lhs;
	RegEx* rhs;
	void free();
};