#include <stdio.h>
#include <string>
#include <stack>
#include <cctype>
#include <iostream>
#include "Set.h"

using namespace std;

string infixToPostfix(string infix);



int evaluate(string infix, const Set& trueValues, const Set& falseValues, string& postfix, bool& result)
{
    stack<ItemType> s;
    
    if(!trueValues.contains(ch) || !falseValues.contains(infix[i]))
        return false;
    
    
}





/*
 There's a bug in the PSEUDOCODE of "infix to postfix"
 Like !!!T will be evaluated as !!T! since the first two '!' we push onto the stack will be poped as we insert the 2nd and the 3rd ‘!’
 When we encounter consecutive '!', the PSEUDOCODE does not work
 
 
 
 So I rewrote a "propably" correct version for '!'
 
IF ch is '!':
    WHILE the stack is not empty AND the stack top is not '('
            AND precedence of ch <= precedence of stack top
            AND the postfix string is not empty
            AND the last char we append to postfix string is an alpha
        append the stack top to postfix
        pop the stack
*/

//Take a postfix of function
//Remove all characters NOT in [!&|()a-z]

string infixToPostfix(string infix)
{
    string postfix = "";
    stack<char> s;
    int len=infix.size();
    int i=0;
    
    while(i<len)
    {
        char ch=infix[i];
        
        if(isalpha(ch))
            postfix+=ch;
        
        switch(ch)
        {
            case '(':
                s.push('(');
                break;
            case ')':
                while(s.top()!='(')
                {
                    postfix+=s.top();
                    s.pop();
                }
                s.pop();
                break;
            case '!':
                while(!s.empty())
                {
                    
                    if(s.top()!='(' && s.top()=='!' && postfix!="" &&
                       (postfix!="" && isalpha(postfix[postfix.size()-1])))
                    {
                        postfix+=s.top();
                        s.pop();
                    }
                    else break;
                }
                
                s.push(ch);
                break;
            case '&':
                while(!s.empty())
                {
                    if(s.top()!='(' && (s.top() == '!' || s.top() == '&'))
                    {
                        postfix+=s.top();
                        s.pop();
                    }
                    else break;
                }
                s.push(ch);
                break;
            case '|':
                while(!s.empty())
                {
                    if(s.top()!='(' && (s.top() == '|' || s.top() == '&'
                                        || s.top()=='!'))
                    {
                        postfix+=s.top();
                        s.pop();
                    }
                    break;
                }
                
                s.push(ch);
                break;
            
                
        }
        i++;
    }
    while(!s.empty())
    {
        postfix+=s.top();
        s.pop();
    }
    return postfix;
}

int main()
{
    //Test infixToPostfix()
    
    assert(infixToPostfix("u") == "u");
    assert(infixToPostfix("(n)") == "n");
    assert(infixToPostfix("a&(s)") == "as&");
    assert(infixToPostfix("a & !s") == "as!&");
    assert(infixToPostfix("!(n|u)") == "nu|!");
    assert(infixToPostfix("u&c&l&a&!(u&s&c)") == "uc&l&a&us&c&!&");
    
    //Test infixToPostfix()
    //Specifically test the occurrence of consecutive
    assert(infixToPostfix(" !!!!!T ")=="T!!!!!");
    assert(infixToPostfix("!F|!!(!!T&!F)") == "F!T!!F!&!!|");
    assert(infixToPostfix("!F&(!F|!!!T)") == "F!F!T!!!|&");
    assert(infixToPostfix(" !F&(!F|!!!T) ")=="F!F!T!!!|&");
    assert(infixToPostfix(" F&(F&T) ")=="FFT&&");
    
    //Test evaluate()
    
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
    
    cout << "Passed all tests" << endl;
    
    
}

