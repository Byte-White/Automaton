#include "AutomatonSerializer.hpp"

std::string AutomatonSerializer::serializeStates(const std::vector<size_t>& container)
{
    std::string result = std::to_string(container.size()) + "\n";
    for (size_t id : container) {
        result += std::to_string(id) + " ";
    }
    result += "\n";
    return result;
}

std::string AutomatonSerializer::serializeTransitions(const Automaton& automaton)
{
    std::string result = std::to_string(automaton.m_transitions.size()) + "\n";
    for (const Transition& transition : automaton.m_transitions)
    {
        result += std::to_string(transition.from) + " "
            + transition.symbol + " "
            + std::to_string(transition.to) + "\n";
    }
    return result;
}

Automaton AutomatonSerializer::deserializeAlphabet(std::istream& is)
{
    std::vector<char> alphabet;
    int alphabetSize;
    if (!(is >> alphabetSize)) {
        return Automaton(std::vector<char>{});
    }

    char c;
    for (int i = 0; i < alphabetSize; i++)
    {
        is >> c;
        alphabet.push_back(c);
    }
    return Automaton(alphabet);
}

void AutomatonSerializer::deserializeStates(Automaton& automaton, std::istream& is)
{
    size_t count;
    size_t stateid;

    is >> count;
    for (size_t i = 0; i < count; i++) {
        is >> stateid;
        automaton.m_states.push_back(stateid);
    }
    is >> count;
    for (size_t i = 0; i < count; i++) {
        is >> stateid;
        automaton.m_startStates.push_back(stateid);
    }
    is >> count;
    for (size_t i = 0; i < count; i++) {
        is >> stateid;
        automaton.m_finalStates.push_back(stateid);
    }
}

void AutomatonSerializer::deserializeTransitions(Automaton& automaton, std::istream& is)
{
    size_t count;
    is >> count;
    for (size_t i = 0; i < count; i++)
    {
        size_t from, to;
        char symbol;
        is >> from >> symbol >> to;
        automaton.addTransition(from, symbol, to);
    }
}

std::string AutomatonSerializer::serialize(const Automaton& automaton)
{
    std::string result = std::to_string(automaton.m_alphabet.size()) + " ";
    for (char c : automaton.m_alphabet) {
        result += c;
    }
    result += "\n";

    result += serializeStates(automaton.m_states);
    result += serializeStates(automaton.m_startStates);
    result += serializeStates(automaton.m_finalStates);
    result += serializeTransitions(automaton);

    return result;
}

Automaton AutomatonSerializer::deserialize(std::istream& is)
{
    Automaton automaton = deserializeAlphabet(is);
    deserializeStates(automaton, is);
    deserializeTransitions(automaton, is);
    return automaton;
}

std::string AutomatonSerializer::toDot(const Automaton& automaton)
{
    std::string result = "digraph Automaton {\n";
    result += "rankdir=LR;\n";
    result += "node [shape=circle];\n";

    for (size_t finalState : automaton.m_finalStates)
    {
        result += std::to_string(finalState) + " [shape=doublecircle];\n";
    }

    for (size_t startState : automaton.m_startStates)
    {
        std::string startNode = "empty_start_" + std::to_string(startState);
        result += startNode + " [label=\"\", shape=point, width=0];\n";
        result += startNode + " -> " + std::to_string(startState) + " [color=\"green\"];\n";
    }

    for (const Transition& transition : automaton.m_transitions)
    {
        result += std::to_string(transition.from) + " -> " + std::to_string(transition.to);
        result += "[label=\"";

        if (transition.symbol == EPSILON)
        {
            result += "(epsilon)";
        }
        else
        {
            result += transition.symbol;
        }

        result += "\"];\n";
    }

    result += "}\n";
    return result;
}

void AutomatonSerializer::print(const Automaton& automaton,std::ostream& os)
{
    os << "States: ";
    for (size_t state : automaton.m_states)
    {
        os << state << " ";
    }
    os << "\nStart: ";
    for (size_t state : automaton.m_startStates)
    {
        os << state << " ";
    }
    os << "\nFinal: ";
    for (size_t state : automaton.m_finalStates)
    {
        os << state << " ";
    }
    os << "\nTransitions:\n";
    for (const auto& transition : automaton.m_transitions)
    {
        os << transition.from << " --" << (transition.symbol == EPSILON ? "(epsilon)" : std::string(1, transition.symbol)) << "--> " << transition.to << "\n";
    }
}
