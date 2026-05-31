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


/**
* @brief Преходът се представя като наредена тройка (from, symbol, to), където from и to са идентификатори на състояния, а symbol е символ от азбуката или епсилон (представен като '\0').
**/
struct Transition
{
    size_t from;
    char symbol;
	size_t to;
};

/**
* @brief Класът Automaton представлява краен автомат, който може да бъде недетерминиран (NFA) или детерминиран (DFA). Той съдържа състоянията и преходите между тях. Класът предоставя методи за създаване на нови състояния, добавяне на преходи, разпознаване на думи, обръщане на автомата, детерминизация и минимизация. Също така включва функции за обединение, конкатенация и звезда на автомати.
**/
class Automaton
{
public:
    friend class AutomatonSerializer;

    /**
	* @brief Конструктор, който приема азбука от символи и създава празен автомат с тази азбука. Автоматът няма състояния или преходи при инициализация.
	* @param alphabet Вектор от символи, представляващи азбуката на автомата.
    **/
    Automaton(const std::vector<char> alphabet);

    /**
	* @brief Създава ново състояние с даден идентификатор и го добавя към автомата. Може да се укаже дали състоянието е начално и/или крайно.
	* @param id Идентификатор на новото състояние. Той трябва да е уникален в рамките на автомата.
	* @param isStart Булева стойност, указваща дали новото състояние е начално.
	* @param isFinal Булева стойност, указваща дали новото състояние е крайно.
	* @exception StateExistsException Ако състоянието с дадения идентификатор вече съществува в автомата, се хвърля изключение от тип StateExistsException.
	* @exception BadSymbolException Ако символът, използван в прехода, не е част от азбуката на автомата и не е епсилон, се хвърля изключение от тип BadSymbolException.
    **/
    void createNewState(size_t id, bool isStart, bool isFinal);

	/**
	* @brief Добавя преход от едно състояние към друго с даден символ. Преходът се представя като наредена тройка (from, symbol, to), където from и to са идентификатори на състояния, а symbol е символ от азбуката или епсилон (представен като '\0').
	* @param from Идентификатор на състоянието, от което започва преходът.
	* @param symbol Символ, който се използва за прехода. Той трябва да е част от азбуката на автомата или да бъде епсилон.
	* @param to Идентификатор на състоянието, към което води преходът.
    **/
    void addTransition(size_t from, char symbol, size_t to);

    /**
	* @brief Проверява дали дадена дума се разпознава от автомата.
	* @param word Низ, представляващ думата, която трябва да се провери.
    **/
    bool recognise(const std::string& word) const;

    /**
	* @brief Връща нов автомат, който е обърнатата версия на текущия автомат. В обърнатия автомат всички преходи са обърнати, началните състояния стават крайни и крайни състояния стават начални.
	* @return Нов автомат, който е обърнатата версия на текущия автомат.
    **/
    Automaton getReversed() const;
    /**
	* @brief Обръща текущия автомат. Всички преходи се обръщат, началните състояния стават крайни и крайни състояния стават начални.
    **/
    void reverse();

    /**
	* @brief Проверява дали автоматът е детерминиран. Автоматът е детерминиран, ако няма две прехода от едно и също състояние с един и същ символ и няма епсилон-преходи.
	* @return true - ако автоматът е детерминиран.
    **/
    bool isDeterministic() const;
    /**
	* @brief Връща нов автомат, който е детерминизираната версия на текущия автомат. Детерминизацията се извършва чрез алгоритъма за конвертиране на NFA в DFA.
    **/
    Automaton getDeterministic() const;

    /**
	* @brief Детерминира текущия автомат.
    **/
	void determinise();

    /**
	* @brief Връща нов автомат, който е минимизираната версия на текущия автомат. Минимизацията се извършва чрез алгоритъма на Бжозовски
    **/
    Automaton getMinimised() const;


    /**
	* @brief Минимизира текущия автомат. Минимизацията се извършва чрез алгоритъма на Бжозовски
    **/
	void minimise();

    /**
	* @brief Функция за обединение на два автомата.
	* @returns Нов автомат(Недетерминиран), който представлява обединението на двата входни автомата. Обединението запазва всички състояния и преходи от двата автомата като новите начални са началните на двата автомата, а новите финални - финалните на двата автомата.
    **/
    friend Automaton Union(const Automaton& lhs, const Automaton& rhs);

    /**
	* @brief Функция за конкатенация на два автомата.
	* @returns Нов автомат(Недетерминиран), който представлява конкатенацията на двата входни автомата. Конкатенацията запазва всички състояния и преходи от двата автомата и добавя епсилон-преходи от всички крайни състояния на първия автомат към началните състояния на втория автомат. Новите начални са началните на първия автомат, а новите финални - финалните на втория автомат.
    **/
    friend Automaton Concat(const Automaton& lhs, const Automaton& rhs);

	/**
	* @brief Функция за звезда на Клини на автомат.
	* @returns Нов автомат(Недетерминиран), който представлява звездата на входния автомат. Звездата запазва всички състояния и преходи от входния автомат и добавя ново начално състояние, което е също така крайно. Добавя епсилон-преходи от това ново начално състояние към всички начални състояния на входния автомат, както и епсилон-преходи от всички крайни състояния на входния автомат към това ново начално състояние.
    **/
    friend Automaton Star(const Automaton& automaton);

    /**
	* @returns азбуката на автомата като вектор от символи.
    **/
    const std::vector<char>& getAlphabet() const
    {
        return m_alphabet;
    }

    ~Automaton() = default;

    /**
	* @returns Броя на състоянията в автомата.
    **/
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