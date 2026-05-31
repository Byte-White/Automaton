#pragma once
#include "RegEx.hpp"
#include "../Utils/UniquePtr.hpp"

/**
* @brief Класът BinaryOperationRegEx е абстрактен базов клас за представяне на бинарни операции между регулярни изрази, като обединение и конкатенация. Той съдържа два указателя към обекти от тип RegEx, които представляват лявата и дясната част на операцията.
**/
class BinaryOperationRegEx : public RegEx
{
protected:
	UniquePtr<RegEx> lhs;
	UniquePtr<RegEx> rhs;
public:
	/**
	* @brief Конструктор, който приема два регулярни израза. Класът копира подадените регулярни изрази.
	* 
	**/
	BinaryOperationRegEx(const RegEx& lhs,const RegEx& rhs);
	/**
	* @brief Конструктор, който приема указатели към два регулярни израза и ги присвоява на членовете на класа. Класът поема собствеността върху тези указатели и ще ги освободи при унищожаване на обекта.
	**/
	BinaryOperationRegEx(RegEx* lhs, RegEx* rhs);
	BinaryOperationRegEx(const BinaryOperationRegEx& other);
	BinaryOperationRegEx& operator=(const BinaryOperationRegEx& other);

	BinaryOperationRegEx(BinaryOperationRegEx&& other) noexcept = default;
	BinaryOperationRegEx& operator=(BinaryOperationRegEx&& other) noexcept = default;
	virtual ~BinaryOperationRegEx() = default;
};