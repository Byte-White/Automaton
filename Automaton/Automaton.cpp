#include "Automaton.hpp"

bool Automaton::hasState(size_t id) const
{
    return std::find(m_states.begin(), m_states.end(), id) != m_states.end();
}

bool Automaton::hasAnyTransitions(size_t state) const
{
    for (const auto& transition : m_transitions)
        if (transition.from == state) return true;
    return false;
}

bool Automaton::symbolIsInAlphabet(char symbol) const
{
    for (char s : m_alphabet)
    {
        if (s == symbol) return true;
    }
    return false;
}

void Automaton::pushStatesWithEpsilon(std::vector<size_t>& closure, std::vector<size_t>& stack, size_t stateId) const
{
    for (const auto& transition : m_transitions)
    {
        if (transition.from == stateId && transition.symbol == EPSILON)
        {
            if (std::find(closure.begin(), closure.end(), transition.to) == closure.end())
            {
                closure.push_back(transition.to);
                stack.push_back(transition.to);
            }
        }
    }
}

std::vector<size_t> Automaton::getEpsilonClosure(const std::vector<size_t>& states) const
{
    std::vector<size_t> closure = states;
    std::vector<size_t> stack = states;

    while (!stack.empty())
    {
        size_t currentState = stack.back();
        stack.pop_back();

        pushStatesWithEpsilon(closure, stack, currentState);
    }
    return closure;
}

std::vector<size_t> Automaton::getNextStates(const std::vector<size_t>& currentStates, char symbol) const
{
    std::vector<size_t> nextStates;

    for (size_t state : currentStates)
    {

        for (const Transition& transition : m_transitions)
        {
            if (transition.from == state && transition.symbol == symbol)
            {
                if (std::find(nextStates.begin(), nextStates.end(), transition.to) == nextStates.end())
                {
                    nextStates.push_back(transition.to);
                }
            }
        }
    }
    return nextStates;
}

bool Automaton::containsFinalState(const std::vector<size_t>& currentStates) const
{
    for (size_t finalState : m_finalStates)
    {
        if (std::find(currentStates.begin(), currentStates.end(), finalState) != currentStates.end())
        {
            return true;
        }
    }
    return false;
}

Automaton::Automaton(const std::vector<char> alphabet)
    : m_alphabet(alphabet)
{

}

void Automaton::createNewState(size_t id, bool isStart, bool isFinal)
{
    if (hasState(id)) throw StateExistsException(id, true);
    m_states.push_back(id);
    if (isStart) m_startStates.push_back(id);
    if (isFinal) m_finalStates.push_back(id);
}

void Automaton::addTransition(size_t from, char symbol, size_t to)
{
    if (!hasState(from)) throw StateExistsException(from, false);
    if (!hasState(to)) throw StateExistsException(to, false);
	if (!symbolIsInAlphabet(symbol)) throw BadSymbolException(symbol);

    m_transitions.push_back({ from, symbol, to });
}

bool Automaton::recognise(const std::string& word) const
{
    std::vector<size_t> currentStates = getEpsilonClosure(m_startStates);

    for (char symbol : word)
    {
        currentStates = getNextStates(currentStates, symbol);
        currentStates = getEpsilonClosure(currentStates);
    }

    return containsFinalState(currentStates);
}

bool Automaton::isDeterministic() const
{
    if (m_startStates.size() > 1) return false;

    for (size_t state : m_states)
    {
        std::vector<char> seenSymbols;
        for (const auto& transition : m_transitions)
        {
            if (transition.from == state)
            {
                if (transition.symbol == EPSILON) return false;
                if (std::find(seenSymbols.begin(), seenSymbols.end(), transition.symbol) != seenSymbols.end())
                {
                    return false;
                }
                seenSymbols.push_back(transition.symbol);
            }
        }
    }

    return true;
}

Automaton Automaton::reverse() const
{
    Automaton reversed(m_alphabet);
    reversed.m_states = m_states;
    reversed.m_finalStates = m_startStates;
    reversed.m_startStates = m_finalStates;

    for (const auto& transition : m_transitions)
    {
        reversed.m_transitions.push_back({ transition.to, transition.symbol, transition.from });
    }

    return reversed;
}

const std::vector<char>& Automaton::getAlphabet() const
{
    return m_alphabet;
}

Automaton::~Automaton() {}
