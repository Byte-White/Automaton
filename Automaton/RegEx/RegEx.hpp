#pragma once
#include <string>
#include "../Automaton/Automaton.hpp"

/**
* @brief Абстрактен базов клас за представяне на регулярни изрази.
**/
class RegEx
{
public:

	/**
	* @brief Връща true, ако дадената дума се разпознава от регулярния израз, и false в противен случай.
	**/
	virtual bool eval(const std::string&) const = 0;
	virtual RegEx* clone() const = 0;

	/**
	* @brief Връща низово представяне на регулярния израз.
	**/
	virtual std::string toString() const = 0;

	/**
	* @brief Връща еквивалентен автомат, който разпознава същия език като регулярния израз. Автоматът може да бъде недетерминиран (NFA) и може да съдържа епсилон-преходи.
	**/
	virtual Automaton toAutomaton() const = 0;

	virtual ~RegEx() = default;

	/**
	* @brief Статична функция, която приема регулярен израз и връща указател към обект от тип RegEx.
	**/
	static RegEx* parse(const std::string& expr);
};