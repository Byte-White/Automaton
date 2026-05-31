#include "RegEx.hpp"

/**
* @brief Класът RangeRegEx представлява регулярни изрази, които са диапазон от символи. Например, [a-z] представлява всички малки букви от a до z.
**/
class RangeRegEx : public RegEx
{
public:
	/**
	* @brief Конструктор, който приема два символа, представляващи началото и края на диапазона, и създава нов обект от тип RangeRegEx.
	**/
	RangeRegEx(char start, char end);
	bool eval(const std::string& word) const override;
	Automaton toAutomaton() const override;
	std::string toString() const override;
	RegEx* clone() const override;
private:
	char m_start;
	char m_end;
};