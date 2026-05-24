#include <iostream>
#include "Automaton.hpp"
#include "UnionRegEx.hpp"
#include "ConcatRegEx.hpp"
#include "StarRegEx.hpp"
#include "LiteralRegEx.hpp"

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
	std::cout << "automaton('abc')" << automaton.recognise("abc") << std::endl;
	automaton.reverse();
	std::cout << "reversed('cba'): " << automaton.recognise("cba") << std::endl;
}

void nonDeterministic()
{
	// has ab
	Automaton automaton({ 'a','b' });
	automaton.createNewState(0, true, false);
	automaton.createNewState(1, false, false);
	automaton.createNewState(2, false, true);
	automaton.addTransition(0, 'a', 0);
	automaton.addTransition(0, 'b', 0);
	automaton.addTransition(0, 'a', 1);
	automaton.addTransition(1, 'b', 2);
	std::cout << "notdet: " << automaton.recognise("abab") << std::endl;
	automaton.print();
	automaton.minimise();
	std::cout << "det min: " << automaton.recognise("abab") << std::endl;;
	automaton.print();
	std::cout << std::endl;
}

void KleeneStar()
{
	Automaton automaton({ 'a', 'b' });
	automaton.createNewState(0, true, false);
	automaton.createNewState(1, false, false);
	automaton.createNewState(2, false, true);
	automaton.addTransition(0, 'a', 1);
	automaton.addTransition(1, 'b', 2);
	automaton = Star(automaton);
	std::cout << automaton.recognise("ababab");
	std::cout << std::endl;
}

void Regex()
{
	std::cout << "(ab+cd).(ef)*\n";
	RegEx* regex = new ConcatRegEx(UnionRegEx(LiteralRegEx("ab"), LiteralRegEx("cd")), StarRegEx(LiteralRegEx("ef")));

	while (true)
	{
		std::string word;
		std::cout << "Enter a word: ";
		std::cin >> word;
		if (word == "exit")
			break;
		std::cout << "regex('" << word << "'): " << regex->eval(word) << std::endl;
	}

	delete regex;
}

int main()
{
	std::cout.flags(std::ios::boolalpha);
	
	std::cout << "--HAS ABBA--"<< std::endl;
	hasABBA();
	std::cout << "--HAS EVEN ONES--"<< std::endl;
	hasEvenOnes();
	std::cout << "--IS ABC--"<< std::endl;
	isABC();
	std::cout << "--DETERMINISE--" << std::endl;
	nonDeterministic();
	std::cout << "--KLEENE STAR--" << std::endl;
	KleeneStar();
	std::cout << "--REGEX--" << std::endl;
	Regex();

}