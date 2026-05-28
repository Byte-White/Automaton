#include "Exception.hpp"


class ParserException : public Exception
{
	int idx;
	std::string expr;
public:
	ParserException(const std::string& message, const std::string& expr, int idx) : Exception(message),expr(expr), idx(idx) {}
	std::string toString() const override
	{
		return Exception::toString() + " at index " + std::to_string(idx) + " in expression: " + expr;
	}
};