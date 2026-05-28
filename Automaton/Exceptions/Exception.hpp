#pragma once
#include <string>

class Exception
{
	const std::string m_message;
public:
	Exception(const std::string& message) : m_message(message) {}
	virtual std::string toString() const { return m_message; }
	virtual ~Exception() = default;
};