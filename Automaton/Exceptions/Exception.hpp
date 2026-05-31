#pragma once
#include <string>


/**
* @brief Базов клас за всички изключения в проекта. Той съдържа съобщение за грешката и предоставя метод toString() за връщане на това съобщение. 
**/
class Exception
{
	const std::string m_message;
public:
	Exception(const std::string& message) : m_message(message) {}
	virtual std::string toString() const { return m_message; }
	virtual ~Exception() = default;
};