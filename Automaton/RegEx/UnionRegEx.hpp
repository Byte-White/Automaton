#pragma once
#include "BinaryOperationRegEx.hpp"


/**
* @brief Класът UnionRegEx представлява обединение на два други регулярни израза.
**/
class UnionRegEx : public BinaryOperationRegEx
{
public:
	/**
	* @brief Конструктор, който приема два регулярни израза и създава нов обект от тип UnionRegEx.
	**/
	UnionRegEx(const RegEx& lhs, const RegEx& rhs) : BinaryOperationRegEx(lhs, rhs) {}

	std::string toString() const override;
	Automaton toAutomaton() const override;
	bool eval(const std::string& word) const override;
	RegEx* clone() const override;
};