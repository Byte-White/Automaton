#pragma once
#include <iostream>
#include <fstream>
#include <string>

#include "Automaton.hpp"
#include "UnionRegEx.hpp"
#include "ConcatRegEx.hpp"
#include "StarRegEx.hpp"
#include "LiteralRegEx.hpp"
#include "RegExParser.hpp"
#include "AutomatonSerializer.hpp"


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
	void openCmd(); 
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