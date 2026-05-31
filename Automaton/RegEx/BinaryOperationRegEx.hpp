#pragma once
#include "RegEx.hpp"

/**
* @brief Класът BinaryOperationRegEx е абстрактен базов клас за представяне на бинарни операции между регулярни изрази, като обединение и конкатенация. Той съдържа два указателя към обекти от тип RegEx, които представляват лявата и дясната част на операцията.
**/
class BinaryOperationRegEx : public RegEx
{
protected:
	RegEx* lhs;
	RegEx* rhs;
public:
	/**
	* @brief Конструктор, който приема два регулярни израза и създава нов обект от тип BinaryOperationRegEx.
	**/
	BinaryOperationRegEx(const RegEx& lhs, const RegEx& rhs);
	BinaryOperationRegEx(const BinaryOperationRegEx& other);
	BinaryOperationRegEx& operator=(const BinaryOperationRegEx& other);
	BinaryOperationRegEx(BinaryOperationRegEx&& other) noexcept;

	BinaryOperationRegEx& operator=(BinaryOperationRegEx&& other) noexcept;

	virtual ~BinaryOperationRegEx();
private:
	void free();
};