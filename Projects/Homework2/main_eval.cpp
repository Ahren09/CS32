//
// Created by Tyler on 2019/01/29.
//
#include "Set.h"  // with ItemType being a type alias for char
#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cassert>
using namespace std;

int evaluate(string infix, const Set& trueValues, const Set& falseValues, string& postfix, bool& result);

int main()
{
    string trueChars  = "tywz";
    string falseChars = "fnx";
    Set trues;
    Set falses;
    for (int k = 0; k < trueChars.size(); k++)
        trues.insert(trueChars[k]);
    for (int k = 0; k < falseChars.size(); k++)
        falses.insert(falseChars[k]);

    string pf;
    bool answer;
    assert(evaluate("w| f", trues, falses, pf, answer) == 0  &&  pf == "wf|" &&  answer);
    assert(evaluate("y|", trues, falses, pf, answer) == 1);
    assert(evaluate("n t", trues, falses, pf, answer) == 1);
    assert(evaluate("nt", trues, falses, pf, answer) == 1);
    assert(evaluate("()", trues, falses, pf, answer) == 1);
    assert(evaluate("y(n|y)", trues, falses, pf, answer) == 1);
    assert(evaluate("t(&n)", trues, falses, pf, answer) == 1);
    assert(evaluate("(n&(t|7)", trues, falses, pf, answer) == 1);
    assert(evaluate("", trues, falses, pf, answer) == 1);
    assert(evaluate("f  |  !f & (t&n) ", trues, falses, pf, answer) == 0
           &&  pf == "ff!tn&&|"  &&  !answer);
    assert(evaluate(" x  ", trues, falses, pf, answer) == 0  &&  pf == "x"  &&  !answer);
    trues.insert('x');
    assert(evaluate("((x))", trues, falses, pf, answer) == 3);
    falses.erase('x');
    assert(evaluate("((x))", trues, falses, pf, answer) == 0  &&  pf == "x"  &&  answer);
    trues.erase('w');
    assert(evaluate("w| f", trues, falses, pf, answer) == 2);
    falses.insert('w');
    assert(evaluate("w| f", trues, falses, pf, answer) == 0  &&  pf == "wf|" &&  !answer);

    assert(evaluate("t(n&)", trues, falses, pf, answer) == 1);
    assert(evaluate("(n!)", trues, falses, pf, answer) == 1);
    assert(evaluate("t(n|)", trues, falses, pf, answer) == 1);
    assert(evaluate("(!!!!!!!n)", trues, falses, pf, answer) == 0  && pf == "n!!!!!!!");
    assert(evaluate("t|&nn", trues, falses, pf, answer) == 1);
    assert(evaluate("t&&nn", trues, falses, pf, answer) == 1);
    assert(evaluate("", trues, falses, pf, answer) == 1);
    assert(evaluate("a()", trues, falses, pf, answer) == 1);
    assert(evaluate("aa|a", trues, falses, pf, answer) == 1);
    assert(evaluate("aa", trues, falses, pf, answer) == 1);
    assert(evaluate("&ab", trues, falses, pf, answer) == 1);
    assert(evaluate("|aa", trues, falses, pf, answer) == 1);
    assert(evaluate(")a", trues, falses, pf, answer) == 1);
    assert(evaluate("((((a))", trues, falses, pf, answer) == 1);
    assert(evaluate("a(|a)", trues, falses, pf, answer) == 1);
    assert(evaluate("a% | a", trues, falses, pf, answer) == 1);
    assert(evaluate("a!", trues, falses, pf, answer) == 1);
    assert(evaluate("!!", trues, falses, pf, answer) == 1);
    assert(evaluate("a(", trues, falses, pf, answer) == 1);
    assert(evaluate("a&", trues, falses, pf, answer) == 1);
    assert(evaluate("a|", trues, falses, pf, answer) == 1);
    assert(evaluate("a!", trues, falses, pf, answer) == 1);

    {
        string trueChars  = "ucla";
        string falseChars = "nsx";
        Set trues;
        Set falses;
        for (int k = 0; k < trueChars.size(); k++)
            trues.insert(trueChars[k]);
        for (int k = 0; k < falseChars.size(); k++)
            falses.insert(falseChars[k]);

        string pf;
        bool answer;
        assert(evaluate("u|c|u", trues, falses, pf, answer) == 0  &&  pf == "uc|u|" &&  answer);
        assert(evaluate("u", trues, falses, pf, answer) == 0  &&  pf == "u" &&  answer);
        assert(evaluate("u&c&l&a & !(u&s&c)", trues, falses, pf, answer) == 0  &&  pf == "uc&l&a&us&c&!&" &&  answer);
        assert(evaluate("(n)", trues, falses, pf, answer) == 0  &&  pf == "n" &&  !answer);
        assert(evaluate("a&(s)", trues, falses, pf, answer) == 0  &&  pf == "as&" &&  !answer);
        assert(evaluate("a & !s", trues, falses, pf, answer) == 0  &&  pf == "as!&" &&  answer);
        assert(evaluate("!(n|u)", trues, falses, pf, answer) == 0  &&  pf == "nu|!" &&  !answer);
        assert(evaluate("!n|u", trues, falses, pf, answer) == 0  &&  pf == "n!u|" &&  answer);
        assert(evaluate("a|n&n", trues, falses, pf, answer) == 0  &&  pf == "ann&|" &&  answer);
        assert(evaluate("a&!(s|u&c|n)|!!!(s&u&n)", trues, falses, pf, answer) == 0  &&  pf == "asuc&|n|!&su&n&!!!|" &&  answer);
    }

    {

        //Test evaluate()

        string trueChars  = "tywz";
        string falseChars = "fnx";
        Set trues;
        Set falses;
        for (int k = 0; k < trueChars.size(); k++)
            trues.insert(trueChars[k]);
        for (int k = 0; k < falseChars.size(); k++)
            falses.insert(falseChars[k]);

        bool answer;

        //Test infixToPostfix()

        string post="";
        assert(evaluate("u",trues, falses, post, answer) != 1 && post == "u");
        assert(evaluate("(n)",trues, falses, post, answer) != 1 && post =="n");
        assert(evaluate("a&(s)",trues, falses, post, answer) != 1 && post == "as&");
        assert(evaluate("a & !s",trues, falses, post, answer) != 1 && post == "as!&");
        assert(evaluate("!(n|u)",trues, falses, post, answer) != 1 && post =="nu|!");
        assert(evaluate("u&c&l&a&!(u&s&c)",trues, falses, post, answer) != 1 && post == "uc&l&a&us&c&!&");

        //Test infixToPostfix()
        //Specifically test the occurrence of consecutive
        assert(evaluate(" !!!!!t ",trues, falses, post, answer) != 1 && post =="t!!!!!");
        assert(evaluate("!f|!!(!!t&!f)",trues, falses, post, answer) != 1 && post =="f!t!!f!&!!|");
        assert(evaluate(" !f&(!f|!!!t) ",trues, falses, post, answer)!= 1 && post =="f!f!t!!!|&");
        assert(evaluate(" f&(f&t) ",trues, falses, post, answer) != 1 && post =="fft&&");

        string pf;
        assert(evaluate("w| f", trues, falses, pf, answer) == 0  &&  pf == "wf|" &&  answer);
        assert(evaluate("y|", trues, falses, pf, answer) == 1);
        assert(evaluate("n t", trues, falses, pf, answer) == 1);
        assert(evaluate("nt", trues, falses, pf, answer) == 1);
        assert(evaluate("()", trues, falses, pf, answer) == 1);
        assert(evaluate("y(n|y)", trues, falses, pf, answer) == 1);
        assert(evaluate("t(&n)", trues, falses, pf, answer) == 1);
        assert(evaluate("(n&(t|7)", trues, falses, pf, answer) == 1);
        assert(evaluate("", trues, falses, pf, answer) == 1);
        assert(evaluate("f  |  !f & (t&n) ", trues, falses, pf, answer) == 0
               &&  pf == "ff!tn&&|"  &&  !answer);
        assert(evaluate(" x  ", trues, falses, pf, answer) == 0  &&  pf == "x"  &&  !answer);
        trues.insert('x');
        assert(evaluate("((x))", trues, falses, pf, answer) == 3);
        falses.erase('x');
        assert(evaluate("((x))", trues, falses, pf, answer) == 0  &&  pf == "x"  &&  answer);
        trues.erase('w');
        assert(evaluate("w| f", trues, falses, pf, answer) == 2);
        falses.insert('w');
        assert(evaluate("w| f", trues, falses, pf, answer) == 0  &&  pf == "wf|" &&  !answer);


        // ***** Test Set 4 *****
        trueChars  = "abcdefg";
        falseChars = "tuvwxyz";
        Set trues_2;
        Set falses_2;
        for (int k = 0; k < trueChars.size(); k++)
            trues_2.insert(trueChars[k]);
        for (int k = 0; k < falseChars.size(); k++)
            falses_2.insert(falseChars[k]);

        assert(evaluate("a&b&c&", trues_2, falses_2, pf, answer) == 1);
        assert(evaluate("))((", trues_2, falses_2, pf, answer) == 1);
        assert(evaluate("(())", trues_2, falses_2, pf, answer) == 1);
        assert(evaluate("((x)", trues_2, falses_2, pf, answer) == 1);
        assert(evaluate("d((&e)(&f))", trues_2, falses_2, pf, answer) == 1);
        assert(evaluate("d((((&e)))((&f)))", trues_2, falses_2, pf, answer) == 1);
        assert(evaluate("d&(!&e)", trues_2, falses_2, pf, answer) == 1);
        assert(evaluate(" !a&(!B|!!!y) ",trues_2,falses_2,pf,answer)==1);
        assert(evaluate("aa",trues_2,falses_2,pf,answer)==1);

        //assert(evaluate(" !a&(!b|!!!y) ",trues_2,falses_2,pf,answer)==0 && pf =="a!b!y!!!|&" && !answer);
        assert(evaluate(" !a&(!b|!!!y) ",trues_2,falses_2,pf,answer)==0 && pf =="a!b!y!!!|&" && !answer);
        assert(evaluate(" (a&u|v)|(!b|!!!!y&x) ",trues_2,falses_2,pf,answer)==0 && pf =="au&v|b!y!!!!x&||" && !answer);

        //Now both sets contain 'z'
        trues_2.insert('z');
        assert(evaluate("d&(!z)", trues_2, falses_2, pf, answer) == 3);

        //Now neither set contain 'z'
        trues_2.erase('t');
        assert(evaluate("t|(a&b&c&d)", trues, falses, pf, answer) == 2);
    }

    cout << "Passed all tests" << endl;
}