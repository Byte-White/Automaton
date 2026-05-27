#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Automaton.hpp"

class AutomatonSerializer
{
private:
    static std::string serializeStates(const std::vector<size_t>& container);

    static std::string serializeTransitions(const Automaton& automaton);

    static Automaton deserializeAlphabet(std::istream& is);

    static void deserializeStates(Automaton& automaton, std::istream& is);

    static void deserializeTransitions(Automaton& automaton, std::istream& is);

    AutomatonSerializer() = default;

public:
    static std::string serialize(const Automaton& automaton);
    static Automaton deserialize(std::istream& is);

    static std::string toDot(const Automaton& automaton);
	static void print(const Automaton& automaton, std::ostream& os = std::cout);
};