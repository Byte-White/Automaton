#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Automaton.hpp"

class AutomatonSerializer
{
public:

    /**
	* @brief Сериализира даден автомат в human-readable формат. 
	* * Форматът на сериализацията е следният:
    * @code
     * <брой_символи_в_азбуката> <символи>
     * <общ_брой_състояния>
     * <състояние_1> ...
     * <брой_начални_състояния>
     * <състояние_1> ...
     * <брой_финални_състояния>
     * <състояние_1> ...
     * <брой_преходи>
     * <from> <symbol> <to>
     * ...
     * @endcode
    **/
    static std::string serialize(const Automaton& automaton);

    /**
	* @brief Десериализира автомат от human-readable формат. Форматът трябва да съответства на този, описан в serialize().
    **/
    static Automaton deserialize(std::istream& is);

    /**
	* @brief Генерира представяне на автомата в DOT формат, който може да бъде визуализиран с инструменти като Graphviz. В DOT представянето, състоянията са възли, а преходите са насочени ръбове между тях. Началните състояния са маркирани със зелени стрелки, а крайните състояния са представени с двойни кръгове.
    **/
    static std::string toDot(const Automaton& automaton);
	
    static void print(const Automaton& automaton, std::ostream& os = std::cout);

private:
    static std::string serializeStates(const std::vector<size_t>& container);

    static std::string serializeTransitions(const Automaton& automaton);

    static Automaton deserializeAlphabet(std::istream& is);

    static void deserializeStates(Automaton& automaton, std::istream& is);

    static void deserializeTransitions(Automaton& automaton, std::istream& is);

    AutomatonSerializer() = default;
};