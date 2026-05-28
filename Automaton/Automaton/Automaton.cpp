#include "Automaton.hpp"

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
	if (!symbolIsInAlphabet(symbol) && symbol!=EPSILON) throw BadSymbolException(symbol);

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

Automaton Automaton::getDeterministic() const
{
    Automaton dfa(m_alphabet);
    std::vector<std::vector<size_t>> stateSubsets;
    stateSubsets.push_back(bubbleSort(getEpsilonClosure(m_startStates)));

    pushReachableSubsets(dfa, stateSubsets);


    for (size_t i = 0; i < stateSubsets.size(); i++)
    {
        dfa.createNewState(i, i == 0, containsFinalState(stateSubsets[i]));
    }

    addSubsetTransitions(dfa, stateSubsets);

    return dfa;
}

void Automaton::determinise()
{
    *this = getDeterministic();
}

Automaton Automaton::getMinimised() const
{
    Automaton minimised = *this;
    minimised.determinise();
    minimised.reverse();
    minimised.determinise();
    minimised.reverse();
    minimised.determinise();
    return minimised;
}

void Automaton::minimise()
{
    *this = getMinimised();
}

Automaton Automaton::getReversed() const
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

void Automaton::reverse()
{
    *this = getReversed();
}

std::vector<size_t> Automaton::bubbleSort(const std::vector<size_t>& arr) const
{
    std::vector<size_t> result = arr;
    int size = arr.size();
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size - i - 1; j++)
        {
            if (result[j] > result[j + 1])
            {
                std::swap(result[j], result[j + 1]);
            }
        }
    }
    return result;
}

void Automaton::pushReachableSubsets(Automaton& dfa, std::vector<std::vector<size_t>>& stateSubsets) const
{
    for (size_t i = 0; i < stateSubsets.size(); i++)
    {
        for (char symbol : m_alphabet)
        {
            std::vector<size_t> nextSubset = bubbleSort(getEpsilonClosure(getNextStates(stateSubsets[i], symbol)));
            if (std::find(stateSubsets.begin(), stateSubsets.end(), nextSubset) == stateSubsets.end())
            {
                stateSubsets.push_back(nextSubset);
            }
        }
    }
}

void Automaton::addSubsetTransitions(Automaton& dfa, const std::vector<std::vector<size_t>>& stateSubsets) const
{
    for (size_t i = 0; i < stateSubsets.size(); i++)
    {
        for (char symbol : dfa.m_alphabet)
        {
            std::vector<size_t> nextSubset = bubbleSort(getEpsilonClosure(getNextStates(stateSubsets[i], symbol)));
            auto it = std::find(stateSubsets.begin(), stateSubsets.end(), nextSubset);
            if (it != stateSubsets.end())
            {
                size_t nextIndex = std::distance(stateSubsets.begin(), it);
                dfa.addTransition(i, symbol, nextIndex);
            }
            else
            {
                throw Exception("Losho: izpusnal si nqkoi subset.");
            }
        }
    }
}

Automaton Union(const Automaton& lhs, const Automaton& rhs)
{
    std::vector<char> newAlphabet = lhs.m_alphabet;
    for (char symbol : rhs.m_alphabet)
    {
        if (!lhs.symbolIsInAlphabet(symbol))
        {
            newAlphabet.push_back(symbol);
        }
    }
    Automaton result(newAlphabet);
    result.m_states = lhs.m_states;
    result.m_startStates = lhs.m_startStates;
    result.m_finalStates = lhs.m_finalStates;
    result.m_transitions = lhs.m_transitions;

    size_t offset = 0;
    for (size_t stateId : lhs.m_states)
        if (offset < stateId) offset = stateId;
    offset++;

    for (size_t stateId : rhs.m_states)
    {
        result.m_states.push_back(stateId + offset);
    }
    for (size_t startState : rhs.m_startStates)
    {
        result.m_startStates.push_back(startState + offset);
    }
    for (size_t finalState : rhs.m_finalStates)
    {
        result.m_finalStates.push_back(finalState + offset);
    }
    for (const auto& transition : rhs.m_transitions)
    {
        result.m_transitions.push_back({ transition.from + offset, transition.symbol, transition.to + offset });
    }
    return result;
}

Automaton Concat(const Automaton& lhs, const Automaton& rhs)
{
    std::vector<char> newAlphabet = lhs.m_alphabet;
    for (char symbol : rhs.m_alphabet)
    {
        if (!lhs.symbolIsInAlphabet(symbol))
        {
            newAlphabet.push_back(symbol);
        }
    }
    Automaton result(newAlphabet);
    result.m_states = lhs.m_states;
    result.m_startStates = lhs.m_startStates;
    result.m_transitions = lhs.m_transitions;

    size_t offset = 0;
    for (size_t stateId : lhs.m_states)
        if (offset < stateId) offset = stateId;
    offset++;

    for (size_t stateId : rhs.m_states)
    {
        result.m_states.push_back(stateId + offset);
    }

    for (size_t finalState : rhs.m_finalStates)
    {
        result.m_finalStates.push_back(finalState + offset);
    }
    for (const auto& transition : rhs.m_transitions)
    {
        result.addTransition(transition.from + offset, transition.symbol, transition.to + offset);
    }

    for (size_t finalState : lhs.m_finalStates)
    {
        for (size_t startState : rhs.m_startStates)
        {
            result.addTransition(finalState, EPSILON, startState + offset);
        }
    }
    return result;
}

Automaton Star(const Automaton& automaton)
{
    Automaton result(automaton.m_alphabet);
    result.m_transitions = automaton.m_transitions;
    result.m_states = automaton.m_states;
    result.m_finalStates = automaton.m_finalStates;

    size_t newStateId = 0;
    for (size_t stateId : automaton.m_states)
    {
        if (stateId >= newStateId) newStateId = stateId + 1;
    }
    result.createNewState(newStateId, true, true);
    for (size_t startState : automaton.m_startStates)
    {
        result.addTransition(newStateId, EPSILON, startState);
    }
    for (size_t finalState : automaton.m_finalStates)
    {
        result.addTransition(finalState, EPSILON, newStateId);
    }
    return result;
}
