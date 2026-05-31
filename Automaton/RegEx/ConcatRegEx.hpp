#pragma once
#include "RegEx.hpp"


/**
* @brief Класът ConcatRegEx е конкатенация на два други регулярни израза. 
**/
class ConcatRegEx : public RegEx
{
public:

	/**
	* @param lhs Левият израз на конкатенацията, който е указател към обект от тип RegEx.
	* @param rhs Десният израз на конкатенацията, който е указател към обект от тип RegEx.
	**/
	ConcatRegEx(const RegEx& lhs, const RegEx& rhs);
	ConcatRegEx(const ConcatRegEx& other);
	ConcatRegEx& operator=(const ConcatRegEx& other);
	virtual ~ConcatRegEx();


	std::string toString() const override;
	Automaton toAutomaton() const override;
	bool eval(const std::string& word) const override;
	RegEx* clone() const override;

private:
	RegEx* lhs;
	RegEx* rhs;
	void free();
};