#pragma once
#include "RegEx.hpp"
#include "StarRegEx.hpp"
#include "UnionRegEx.hpp"
#include "ConcatRegEx.hpp"
#include "LiteralRegEx.hpp"


/**
* @brief Класът RegExParser използва рекурсивен парсер за обработка на различните оператори в регулярните изрази, като обединение (+), конкатенация(без оператор) и звезда (*). За празна дума се използва символът '@'.
**/
class RegExParser
{
public:
	/**
	* @brief Конструктор, който приема регулярен израз.
	**/
	RegExParser(const std::string& expr);

	/**
	* @brief Функция, която парсва регулярния израз и връща указател към обект от тип RegEx, който представлява този израз.
	* @exception ParserException Ако по време на парсването се срещне синтактична грешка, се хвърля изключение от тип ParserException, което съдържа информация за грешката и позицията в израза, където е възникнала.
	**/
	RegEx* parse();
private:
	RegEx* parseUnion();
	RegEx* parseConcat();
	RegEx* parseStar();
	RegEx* parseBrackets();
	RegEx* parseLiteral();
	std::string m_expr;
	size_t m_idx;
	char peek() const;
	char get();
};