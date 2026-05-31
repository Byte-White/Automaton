#pragma once
#include "BinaryOperationRegEx.hpp"


/**
* @brief Класът UnionRegEx представлява обединение на два други регулярни израза.
**/
class UnionRegEx : public BinaryOperationRegEx
{
public:
	/**
	* @brief Конструктор, който приема два регулярни израза и създава нов обект от тип UnionRegEx. Класът копира подадените регулярни изрази.
	**/
	UnionRegEx(const RegEx& lhs, const RegEx& rhs);
	/**
	* @brief Конструктор, който приема указатели към два регулярни израза и създава обект от тип UnionRegEx. Класът поема собствеността върху тези указатели и ще ги освободи при унищожаване на обекта.
	**/
	UnionRegEx(RegEx* lhs, RegEx* rhs);

	std::string toString() const override;
	Automaton toAutomaton() const override;
	bool eval(const std::string& word) const override;
	RegEx* clone() const override;
};