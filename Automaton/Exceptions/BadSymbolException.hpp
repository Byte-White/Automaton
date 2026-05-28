#include "Exception.hpp"

class BadSymbolException : public Exception
{
	char m_symbol;
public:
	BadSymbolException(char symbol) : Exception("Symbol '" + std::string(1, symbol) + "' is not in the alphabet."), m_symbol(symbol) {}
	virtual ~BadSymbolException() = default;
};