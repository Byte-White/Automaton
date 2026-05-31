#include "RegEx.hpp"
#include "RegExParser.hpp"


UniquePtr<RegEx> RegEx::parse(const std::string& expr)
{
	RegExParser parser(expr);
	return parser.parse();
}
