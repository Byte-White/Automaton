#include "RegExParser.hpp"
#include "Exception.hpp"
#include "ParserException.hpp"

RegExParser::RegExParser(const std::string& expr)
	:m_expr(expr), m_idx(0)
{
}

RegEx* RegExParser::parse()
{
	RegEx* result = parseUnion();

	if (peek() != '\0')
	{
		delete result;
		throw ParserException("Unexpected character", m_expr, m_idx);
	}

	return result;
}

RegEx* RegExParser::parseUnion()
{
	RegEx* left = parseConcat();

	while (peek() == '+')
	{
		get();
		RegEx* right = parseConcat();

		RegEx* temp = new UnionRegEx(*left, *right);

		delete left;
		delete right;

		left = temp;
	}

	return left;
}

RegEx* RegExParser::parseConcat()
{
	RegEx* left = parseStar();

	while (true)
	{
		char c = peek();

		if (c == '\0' || c == ')' || c == '+')
			break;

		RegEx* right = parseStar();

		RegEx* temp = new ConcatRegEx(*left, *right);

		delete left;
		delete right;

		left = temp;
	}

	return left;

}

RegEx* RegExParser::parseStar()
{
	RegEx* expr = nullptr;

	if (peek() == '(')
		expr = parseBrackets();
	else
		expr = parseLiteral();

	while (peek() == '*')
	{
		get();
		RegEx* temp = new StarRegEx(*expr);
		delete expr;
		expr = temp;
	}

	return expr;
}

RegEx* RegExParser::parseBrackets()
{
	if (get() != '(')
		throw ParserException("Expected '('", m_expr, m_idx);

	RegEx* inside = parseUnion();

	if (get() != ')')
	{
		delete inside;
		throw ParserException("Expected ')'", m_expr, m_idx);
	}

	return inside;
}

RegEx* RegExParser::parseLiteral()
{
	std::string word;
	while (true)
	{
		char c = peek();
		if (c == '\0' || c == '(' || c == ')' || c == '*' || c == '+')
			break;
		word += get();
	}
	return new LiteralRegEx(word);
}

char RegExParser::peek() const
{
	if (m_idx < m_expr.size())
		return m_expr[m_idx];
	return '\0';
}

char RegExParser::get()
{
	if (m_idx < m_expr.size())
		return m_expr[m_idx++];
	return '\0';
}
