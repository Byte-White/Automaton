#pragma once
#include <iostream>
#include <fstream>
#include <string>

#include "../Automaton/Automaton.hpp"
#include "../RegEx/UnionRegEx.hpp"
#include "../RegEx/ConcatRegEx.hpp"
#include "../RegEx/StarRegEx.hpp"
#include "../RegEx/LiteralRegEx.hpp"
#include "../RegEx/RegExParser.hpp"
#include "../Automaton/AutomatonSerializer.hpp"



/**
* @brief Класът AutomatonCLI предоставя интерфейс за команден ред, който позволява на потребителите да взаимодействат с автомати и регулярни изрази. Чрез този интерфейс потребителите могат да създават, модифицират, запазват и зареждат автомати, както и да извършват различни операции като детерминизация, минимизация, обединение, конкатенация и звезда. CLI-то също така поддържа разпознаване на думи от автоматите и визуализация на автоматите чрез DOT формат.
**/
class AutomatonCLI
{
	struct IdAutomaton
	{
		size_t id;
		Automaton automaton;
	};
	std::vector<IdAutomaton> m_automatons;
	Automaton& getAutomatonById(size_t id);
	void removeAutomatonById(size_t id);
	void addAutomaton(const Automaton& automaton);
	bool m_isRunning = true;
	size_t idCounter = 0;
	size_t getNextId();
	void reset();
public:
	void run();
	void helpCmd();
	void exitCmd();
	void loadCmd(bool restartList); 
    void saveCmd();
    void saveAllCmd();
    void listCmd();
    void printCmd();
    void removeCmd();
	void resetCmd();
    void deterministicCmd();
    void determiniseCmd();
    void reverseCmd();
    void minimiseCmd();
    void recogniseCmd();
    void unionCmd();
    void concatCmd();
    void starCmd();
    void regCmd();
    void drawCmd();
};