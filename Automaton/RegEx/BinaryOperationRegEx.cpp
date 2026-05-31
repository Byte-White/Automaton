#include "BinaryOperationRegEx.hpp"



BinaryOperationRegEx::BinaryOperationRegEx(const RegEx& lhs,const RegEx& rhs)
{
	this->lhs.reset(lhs.clone());
	this->rhs.reset(rhs.clone());
}

BinaryOperationRegEx::BinaryOperationRegEx(RegEx* lhs, RegEx* rhs) : lhs(lhs), rhs(rhs) {}

BinaryOperationRegEx::BinaryOperationRegEx(const BinaryOperationRegEx& other) : lhs(other.lhs->clone()), rhs(other.rhs->clone()) {}

BinaryOperationRegEx& BinaryOperationRegEx::operator=(const BinaryOperationRegEx& other)
{
	if (this != &other)
	{
		lhs.reset(other.lhs->clone());
		rhs.reset(other.rhs->clone());
	}
	return *this;
}