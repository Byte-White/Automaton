#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Automaton.hpp"
#include "RegExParser.hpp"

Automaton createSimpleAutomaton(char c) {
    Automaton aut({ c });
    aut.createNewState(0, true, false);
    aut.createNewState(1, false, true);
    aut.addTransition(0, c, 1);
    return aut;
}

TEST_CASE("Exceptions(StateExists, BadSymbol)") 
{
    Automaton aut({ 'a' });
    aut.createNewState(0, true, false);

    CHECK_THROWS_AS(aut.createNewState(0, false, false), StateExistsException);

    CHECK_THROWS_AS(aut.addTransition(0, 'a', 99), StateExistsException);
    CHECK_THROWS_AS(aut.addTransition(99, 'a', 0), StateExistsException);

    CHECK_THROWS_AS(aut.addTransition(0, 'z', 0), BadSymbolException);
}

TEST_CASE("Recognise") 
{
    Automaton empty_lang({ 'a', 'b' });
    empty_lang.createNewState(0, true, true);

    CHECK(empty_lang.recognise("") == true);
    CHECK(empty_lang.recognise("a") == false);

    Automaton a_lang = createSimpleAutomaton('a');
    CHECK(a_lang.recognise("a") == true);
    CHECK(a_lang.recognise("") == false);
    CHECK(a_lang.recognise("aa") == false);
}

TEST_CASE("Union") {
    Automaton a_lang = createSimpleAutomaton('a');
    Automaton b_lang = createSimpleAutomaton('b');

    Automaton union_ab = Union(a_lang, b_lang);

    CHECK(union_ab.recognise("a") == true);
    CHECK(union_ab.recognise("b") == true);
    CHECK(union_ab.recognise("") == false);
    CHECK(union_ab.recognise("ab") == false);
}

TEST_CASE("Concat") {
    Automaton a_lang = createSimpleAutomaton('a');
    Automaton b_lang = createSimpleAutomaton('b');

    Automaton concat_ab = Concat(a_lang, b_lang);

    CHECK(concat_ab.recognise("ab") == true);
    CHECK(concat_ab.recognise("a") == false);
    CHECK(concat_ab.recognise("b") == false);
    CHECK(concat_ab.recognise("ba") == false);
}

TEST_CASE("Star") {
    Automaton a_lang = createSimpleAutomaton('a');

    Automaton star_a = Star(a_lang);

    CHECK(star_a.recognise("") == true);
    CHECK(star_a.recognise("a") == true);
    CHECK(star_a.recognise("aaaaa") == true);
    CHECK(star_a.recognise("ab") == false);
}

TEST_CASE("Regex to automaton") 
{
	RegEx* regex = RegEx::parse("a(b+c)+a");
	Automaton aut = regex->toAutomaton();

    CHECK(regex->eval("a") == true);
    CHECK(aut.recognise("a") == regex->eval("a"));

    CHECK(regex->eval("ab") == true);
    CHECK(aut.recognise("ab") == regex->eval("ab"));

    CHECK(regex->eval("ac") == true);
    CHECK(aut.recognise("ac") == regex->eval("ac"));

    CHECK(regex->eval("aba") == false);
	CHECK(aut.recognise("aba") == regex->eval("aba"));
}

TEST_CASE("isDeterministic") {
    Automaton aut({ 'a' });
    aut.createNewState(0, true, false);
    aut.createNewState(1, false, true);
    aut.addTransition(0, 'a', 1);

    CHECK(aut.isDeterministic() == true);
    
    aut.createNewState(2, false, false);
    aut.addTransition(0, 'a', 2);

    CHECK(aut.isDeterministic() == false);
}

TEST_CASE("Determinise") 
{
    Automaton nfa({ 'a' });
    nfa.createNewState(0, true, false);
    nfa.createNewState(1, false, true);
    nfa.createNewState(2, false, true);

    nfa.addTransition(0, 'a', 1);
    nfa.addTransition(0, 'a', 2);

    CHECK(nfa.isDeterministic() == false);

    nfa.determinise();

    CHECK(nfa.isDeterministic() == true);
    CHECK(nfa.recognise("a") == true);
    CHECK(nfa.recognise("aa") == false);
}

TEST_CASE("Reverse")
{
    Automaton aut({ 'a', 'b' });
    aut.createNewState(0, true, false);
    aut.createNewState(1, false, false);
    aut.createNewState(2, false, true);
    aut.addTransition(0, 'a', 1);
    aut.addTransition(1, 'b', 2);
    CHECK(aut.recognise("ab") == true);
    CHECK(aut.recognise("a") == false);
    CHECK(aut.recognise("b") == false);
    CHECK(aut.recognise("ba") == false);
    aut.reverse();
    CHECK(aut.recognise("ab") == false);
    CHECK(aut.recognise("a") == false);
    CHECK(aut.recognise("b") == false);
    CHECK(aut.recognise("ba") == true);

}