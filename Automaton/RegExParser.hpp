#pragma once
#include "RegEx.hpp"
#include "StarRegEx.hpp"
#include "UnionRegEx.hpp"
#include "ConcatRegEx.hpp"
#include "LiteralRegEx.hpp"


class RegExParser
{
public:
	RegExParser(const std::string& expr);
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