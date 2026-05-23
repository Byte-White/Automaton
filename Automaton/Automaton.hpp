#pragma once
#include <map>
#include <vector>
#include <string>
#include <algorithm>

#include "Exception.hpp"
#include "StateExistsException.hpp"
#include "BadSymbolException.hpp"

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

    Automaton(const std::vector<char> alphabet);


    void createNewState(size_t id, bool isStart, bool isFinal);

    void addTransition(size_t from, char symbol, size_t to);

    bool recognise(const std::string& word) const;

    bool isDeterministic() const;

    Automaton reverse() const;

    const std::vector<char>& getAlphabet() const;

    ~Automaton();

private:
    bool hasState(size_t id) const;
    bool hasAnyTransitions(size_t state) const;
    bool symbolIsInAlphabet(char symbol) const;


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