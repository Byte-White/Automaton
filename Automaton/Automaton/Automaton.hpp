#pragma once
#include <map>
#include <vector>
#include <string>
#include <set>
#include <iostream>

#include "../Exceptions/Exception.hpp"
#include "../Exceptions/StateExistsException.hpp"
#include "../Exceptions/BadSymbolException.hpp"

constexpr char EPSILON = '\0';

struct Transition
{
    size_t from;
    char symbol;
	size_t to;
};

class Automaton
{
public:
    friend class AutomatonSerializer;

    Automaton(const std::vector<char> alphabet);

    void createNewState(size_t id, bool isStart, bool isFinal);

    void addTransition(size_t from, char symbol, size_t to);

    bool recognise(const std::string& word) const;


    Automaton getReversed() const;
    void reverse();

    bool isDeterministic() const;
    Automaton getDeterministic() const;

	void determinise();

    Automaton getMinimised() const;

	void minimise();

    friend Automaton Union(const Automaton& lhs, const Automaton& rhs);

    friend Automaton Concat(const Automaton& lhs, const Automaton& rhs);

    friend Automaton Star(const Automaton& automaton);

    const std::vector<char>& getAlphabet() const
    {
        return m_alphabet;
    }

    ~Automaton() = default;

	size_t getStatesCount() const
	{
		return m_states.size();
	}

private:
    bool hasState(size_t id) const
    {
        for (size_t state : m_states)
            if (state == id) return true;
        return false;
    }
    bool hasAnyTransitions(size_t state) const
    {
        for (const Transition& transition : m_transitions)
            if (transition.from == state) return true;
        return false;
    }
    bool symbolIsInAlphabet(char symbol) const
    {
        for (char s : m_alphabet)
        {
            if (s == symbol) return true;
        }
        return false;
    }

    std::vector<size_t> bubbleSort(const std::vector<size_t>& arr) const;

    void pushReachableSubsets(Automaton& dfa, std::vector<std::vector<size_t>>& stateSubsets) const;

    void addSubsetTransitions(Automaton& dfa, const std::vector<std::vector<size_t>>& stateSubsets) const;


    void pushStatesWithEpsilon(std::vector<size_t>& closure, std::vector<size_t>& stack, size_t stateId) const;
    
    std::vector<size_t> getEpsilonClosure(const std::vector<size_t>& states) const;
    std::vector<size_t> getNextStates(const std::vector<size_t>& currentStates, char symbol) const;
    
    bool containsFinalState(const std::vector<size_t>& currentStates) const;
private:
    std::vector<size_t> m_states;
    std::vector<size_t> m_startStates;
    std::vector<size_t> m_finalStates;

    std::vector<Transition> m_transitions;
    std::vector<char> m_alphabet;
};