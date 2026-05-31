#include "RegExParser.hpp"
#include "../Exceptions/Exception.hpp"
#include "../Exceptions/ParserException.hpp"

bool isSpecialChar(char c)
{
    return c == '\0' || c == '(' || c == ')' || c == '+' || c == '*' || c == '[' || c == ']';
}

RegExParser::RegExParser(const std::string& expr)
    : m_expr(expr), m_idx(0)
{
}

UniquePtr<RegEx> RegExParser::parse()
{
    UniquePtr<RegEx> result = parseUnion();

    if (peek() != '\0')
    {
        throw ParserException("Unexpected character", m_expr, m_idx);
    }

    return result;
}

UniquePtr<RegEx> RegExParser::parseUnion()
{
    UniquePtr<RegEx> left = parseConcat();

    while (peek() == '+')
    {
        get();
        UniquePtr<RegEx> right = parseConcat();
        left.reset(new UnionRegEx(left.release(), right.release()));
    }

    return left;
}

UniquePtr<RegEx> RegExParser::parseConcat()
{
    UniquePtr<RegEx> left = parseStar();

    while (true)
    {
        char c = peek();

        if (c == '\0' || c == ')' || c == '+')
            break;

        UniquePtr<RegEx> right = parseStar();
        left.reset(new ConcatRegEx(left.release(), right.release()));
    }

    return left;
}

UniquePtr<RegEx> RegExParser::parseStar()
{
    UniquePtr<RegEx> expr = nullptr;

    if (peek() == '(')
        expr = parseParentheses();
    else if (peek() == '[')
        expr = parseBrackets();
    else
        expr = parseLiteral();

    while (peek() == '*')
    {
        get();
        expr.reset(new StarRegEx(expr.release()));
    }

    return expr;
}

UniquePtr<RegEx> RegExParser::parseParentheses()
{
    get();

    UniquePtr<RegEx> inside = parseUnion();

    if (get() != ')')
    {
        throw ParserException("Expected ')'", m_expr, m_idx - 1);
    }

    return inside;
}

UniquePtr<RegEx> RegExParser::parseBrackets()
{
    get();

    char start = get();
    if (isSpecialChar(start))
    {
        throw ParserException("Expected a start symbol", m_expr, m_idx - 1);
    }
    if (get() != '-')
    {
        throw ParserException("Expected '-'", m_expr, m_idx - 1);
    }

    char end = get();
    if (isSpecialChar(end))
    {
        throw ParserException("Expected an end symbol", m_expr, m_idx - 1);
    }

    if (get() != ']')
    {
        throw ParserException("Expected ']'", m_expr, m_idx - 1);
    }

    return UniquePtr<RegEx>(new RangeRegEx(start, end));
}

UniquePtr<RegEx> RegExParser::parseLiteral()
{
    char c = get();

    if (c == '@')
        return UniquePtr<RegEx>(new LiteralRegEx(""));

    if (isSpecialChar(c))
    {
        throw ParserException("Expected a literal", m_expr, m_idx - 1);
    }

    return UniquePtr<RegEx>(new LiteralRegEx(std::string(1, c)));
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