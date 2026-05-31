#pragma once
#include "Exception.hpp"



/**
* @brief Изключение, което се хвърля при опит за създаване на състояние с идентификатор, който вече съществува в автомата, или при опит за достъп до несъществуващо състояние. Съдържа информация за идентификатора на състоянието и дали то вече съществува или не.
**/
class StateExistsException : public Exception
{
	size_t m_id;
	bool m_exists;
public:
	StateExistsException(size_t id, bool exists) : Exception(""), m_id(id), m_exists(exists) {}
	std::string toString() const override
	{
		return "State " + std::to_string(m_id) + (m_exists ? " already exists." : " does not exist.");
	}

	bool exists() const { return m_exists; }
	size_t id() const { return m_id; }
	virtual ~StateExistsException() = default;
};