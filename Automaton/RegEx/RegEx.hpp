#pragma once
#include <string>
#include "../Automaton/Automaton.hpp"

class RegEx
{
public:
	virtual bool eval(const std::string&) const = 0;
	virtual RegEx* clone() const = 0;
	virtual std::string toString() const = 0;
	virtual Automaton toAutomaton() const = 0;
	virtual ~RegEx() = default;
	static RegEx* parse(const std::string& expr);
};