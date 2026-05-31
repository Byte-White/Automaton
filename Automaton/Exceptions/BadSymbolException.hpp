#include "Exception.hpp"


/**
* @brief Изключение, което се хвърля при опит за използване на символ, който не е част от азбуката на автомата. Съдържа информация за символа, който е бил използван и не е валиден.
**/
class BadSymbolException : public Exception
{
	char m_symbol;
public:
	BadSymbolException(char symbol) : Exception("Symbol '" + std::string(1, symbol) + "' is not in the alphabet."), m_symbol(symbol) {}
	virtual ~BadSymbolException() = default;
};