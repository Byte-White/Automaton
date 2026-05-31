#pragma once
#include "RegEx.hpp"
#include "../Utils/UniquePtr.hpp"


/**
* @brief Класът StarRegEx представлява регулярни изрази, които са звезда на друг регулярен израз.
**/
class StarRegEx : public RegEx
{
public:
	/**
	* @brief Конструктор, който приема друг регулярен израз и създава звезда на този израз. Класът копира подадения регулярен израз.
	**/
	StarRegEx(const RegEx& inner);
	/**
	* @brief Конструктор, който приема друг регулярен израз и създава звезда на този израз. Собствеността върху указателя се поема от класа StarRegEx, който ще го освободи при унищожаване на обекта.
	**/
	StarRegEx(RegEx* inner);
	StarRegEx(const StarRegEx& other);
	StarRegEx& operator=(const StarRegEx& other);

	StarRegEx(StarRegEx&& other) noexcept = default;
	StarRegEx& operator=(StarRegEx&& other) noexcept = default;
	virtual ~StarRegEx() = default;

	bool eval(const std::string& word) const override;
	Automaton toAutomaton() const override;
	std::string toString() const override;
	RegEx* clone() const override;
private:
	UniquePtr<RegEx> inner;
};