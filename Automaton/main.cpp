#include <iostream>
#include "Automaton.hpp"

void hasABBA()
{
	Automaton automaton({'a', 'b'});
	automaton.createNewState(0, true, false);
	automaton.createNewState(1, false, false);
	automaton.createNewState(2, false, false);
	automaton.createNewState(3, false, false);
	automaton.createNewState(4, false, true);
	automaton.addTransition(0, 'a', 0);
	automaton.addTransition(0, 'b', 0);
	automaton.addTransition(0, 'a', 1);
	automaton.addTransition(1, 'b', 2);
	automaton.addTransition(2, 'b', 3);
	automaton.addTransition(3, 'a', 4);
	automaton.addTransition(4, 'a', 4);
	automaton.addTransition(4, 'b', 4);

	std::cout.flags(std::ios::boolalpha);
	std::cout << "automaton('abba'): "  << automaton.recognise("abba") << std::endl;
}

void hasEvenOnes()
{
	Automaton automaton({ '0', '1' });
	automaton.createNewState(0, true, true);
	automaton.createNewState(1, false, false);	
	automaton.addTransition(0, '0', 0);
	automaton.addTransition(0, '1', 1);
	automaton.addTransition(1, '0', 1);
	automaton.addTransition(1, '1', 0);

	std::cout.flags(std::ios::boolalpha);
	std::cout << "automaton('101'): " << automaton.recognise("101") << std::endl;

}

void isABC()
{
	Automaton automaton({ 'a', 'b', 'c' });
	automaton.createNewState(0, true, false);
	automaton.createNewState(1, false, false);
	automaton.createNewState(2, false, false);
	automaton.createNewState(3, false, true);
	automaton.addTransition(0, 'a', 1);
	automaton.addTransition(1, 'b', 2);
	automaton.addTransition(2, 'c', 3);
	std::cout.flags(std::ios::boolalpha);
	std::cout << "automaton('abc')" << automaton.recognise("abc") << std::endl;
	automaton = automaton.reverse();
	std::cout << "reversed('cba'): " << automaton.recognise("cba") << std::endl;
}

int main()
{
	std::cout << "--HAS ABBA--"<< std::endl;
	hasABBA();
	std::cout << "--HAS EVEN ONES--"<< std::endl;
	hasEvenOnes();
	std::cout << "--IS ABC--"<< std::endl;
	isABC();
}