#include "BinaryOperationRegEx.hpp"


/**
* @brief Конструктор, който приема два регулярни израза и създава нов обект от тип BinaryOperationRegEx.
**/

BinaryOperationRegEx::BinaryOperationRegEx(const RegEx& lhs, const RegEx& rhs) : lhs(lhs.clone()), rhs(rhs.clone()) {}

BinaryOperationRegEx::BinaryOperationRegEx(const BinaryOperationRegEx& other) : lhs(other.lhs->clone()), rhs(other.rhs->clone()) {}

BinaryOperationRegEx& BinaryOperationRegEx::operator=(const BinaryOperationRegEx& other)
{
	if (this != &other)
	{
		free();
		lhs = other.lhs->clone();
		rhs = other.rhs->clone();
	}
	return *this;
}

BinaryOperationRegEx::BinaryOperationRegEx(BinaryOperationRegEx&& other) noexcept : lhs(other.lhs), rhs(other.rhs)
{
	other.lhs = nullptr;
	other.rhs = nullptr;
}

BinaryOperationRegEx& BinaryOperationRegEx::operator=(BinaryOperationRegEx&& other) noexcept
{
	if (this != &other)
	{
		free();
		lhs = other.lhs;
		rhs = other.rhs;
		other.lhs = nullptr;
		other.rhs = nullptr;
	}
	return *this;
}

BinaryOperationRegEx::~BinaryOperationRegEx()
{
	free();
}

void BinaryOperationRegEx::free()
{
	delete lhs;
	delete rhs;
}
