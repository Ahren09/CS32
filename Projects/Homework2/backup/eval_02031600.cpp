#include <stdio.h>
#include <string>
#include <stack>
#include <cctype>
#include <iostream>
#include <cassert>
#include "Set.h"

using namespace std;

int infixToPostfix(string infix,string& postfix);
int checkBracket(const string& infix);
int checkAlphaAndOperator(const string& infix);

// MARK: evaluate
int evaluate(string infix, const Set& trueValues, const Set& falseValues, string& postfix, bool& result)
{
    //Store
    Set op;
    op.insert('!');
    op.insert('&');
    op.insert('|');
    op.insert('(');
    op.insert(')');
    op.insert(' ');
    
    //IF infix is empty
    if(infix=="" )
        return 1;
    
    
    //IF infix string contains char other than lowercase alpha and operators
    
    int n_left=0, n_right=0;
    for(int i=0;i!=infix.size();i++)
    {
        if(infix[i]=='(')
            n_left++;
        else if(infix[i]==')')
            n_right++;
        if(i>0)
            if(islower(infix[i-1]) && islower(infix[i]))
                return 1;
        if(!op.contains(infix[i]) && !islower(infix[i]))
            return 1;
    }
    if(n_left!=n_right)
        return 1;
    

    //Convert infix string to postfix format
    
    if(infixToPostfix(infix,postfix)==1)
        return 1;;
    
    int pf_size=postfix.size();
    if(pf_size==0)
        return 1;
    
    if(checkBracket(infix)==1 || checkAlphaAndOperator(infix)==1)
        return 1;
    
    stack<bool> s;
    
    for(int i=0;i<pf_size;i++)
    {
        
        //IF pf[i] is a char
        if(islower(postfix[i]))
        {
            //pf[i] is in NEITHER set OR BOTH sets
            if(!trueValues.contains(postfix[i]) && !falseValues.contains(postfix[i]))
                return 2;
            else if(trueValues.contains(postfix[i]) && falseValues.contains(postfix[i]))
                return 3;
            
            //pf[i] is in either set
            else{
                if(trueValues.contains(postfix[i]))
                    s.push(true);
                else if(falseValues.contains(postfix[i]))
                    s.push(false);
            }
        }
        
        //pf[i] is an operator
        else
        {
            if(postfix[i] == '!')
            {
                if(s.empty())
                    return 1;
                bool b=s.top();
                s.pop();
                s.push(!b);
                
            }
            else
            {
                if(s.size()<2)
                    return 1;
                bool b2=s.top();
                s.pop();
                bool b1=s.top();
                s.pop();
                if(postfix[i]=='&')
                    s.push(b1&&b2);
                else if(postfix[i]=='|')
                    s.push(b1||b2);
            }
            
        }
        
        
    }
    result = s.top();
    s.pop();
    
    //RETURN FALSE IF there is more than 1 boolean in stack
    //e.g., the infix contains consecutive chars
    if(!s.empty())
        return 1;
    return 0;
    
    
}





/*
 The condition for '!' is different from that of '&' and '|'
 I rewrote a separate pseudocode for '!'
 
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


// MARK: infixToPostfix
int infixToPostfix(string infix,string& postfix)
{
    postfix="";
    stack<char> s;
    int len=infix.size();
    int i=0;
    
    while(i<len)
    {
        char ch=infix[i];
        
        if(islower(ch))
            postfix+=ch;
        
        switch(ch)
        {
            case '(':
                s.push('(');
                break;
            case ')':
                while(!s.empty() && s.top()!='(')
                {
                    postfix+=s.top();
                    s.pop();
                }
                if(!s.empty())
                {
                    s.pop();
                    break;
                }
                else
                    return 1;
                
            case '!':
                while(!s.empty())
                {
                    
                    if(s.top()!='(' && s.top()=='!' && postfix!="" &&
                       (postfix!="" && islower(postfix[postfix.size()-1])))
                    {
                        if(postfix=="")
                            return 1;
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
                        if(postfix=="")
                            return 1;
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
    return 0;
}

// MARK: checkAlphaAndOperator
int checkAlphaAndOperator(const string& infix)
{
    int len=infix.size();
    int n_alpha=0, n_other=0;
    
    //Check invalid infix format: "a!" AND "a!a!"
    if(len>=2)
    {
       if(islower(infix[0]) && infix[1]=='!')
            return 1;
    }
        
    
    
    //Check invalid infix format: number of operands less than or equal to operators
    for(int i=0;i<len;i++)
    {
        if(islower(infix[i]))
            n_alpha++;
        else if(infix[i]=='&' || infix[i]=='|')
            n_other++;
    }
    if(n_alpha<=n_other && n_alpha!=0)
        return 1;
    else return 0;
    
}

// MARK: checkBracket
int checkBracket(const string& infix)
{
    
    
    int len=infix.size();
    
    int l=0, r=0;
    int n_alpha=0, n_other=0;
    
    
    while(l<len)
    {
        //IF '(' is found, leave l at original position and move r
        if(infix[l]=='(')
        {
            r=l+1;
            while(r<len && infix[r]!='(')
            {
                r++;
                if(infix[r]==')')
                {
                    //Check invalid format: Empty bracket
                    if(infix[r-1]=='(')
                        return 1;
                    for(int i=l;i<r;i++)
                    {
                        if(islower(infix[i]))
                            n_alpha++;
                        else if(infix[i]=='&' || infix[i]=='|')
                            n_other++;
                    }
                }
                
            }
        }
        if (n_alpha<=n_other && n_alpha!=0)
            return 1;
        
        l++;
        r=l;
        
    }
    return 0;
}


// MARK: main
int main()
{
    //Test infixToPostfix()
    
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
    assert(evaluate("f  |  !f & (t&n) ", trues, falses, pf, answer) == 0  &&  pf == "ff!tn&&|"  &&  !answer);
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
//    assert(evaluate("(n!)", trues, falses, pf, answer) == 1); //$
    assert(evaluate("t(n|)", trues, falses, pf, answer) == 1);
    assert(evaluate("(!!!!!!!n)", trues, falses, pf, answer) == 0  && pf == "n!!!!!!!");
    assert(evaluate("t|&nn", trues, falses, pf, answer) == 1); //$
    assert(evaluate("t&&nn", trues, falses, pf, answer) == 1);
    assert(evaluate("", trues, falses, pf, answer) == 1);
//    assert(evaluate("a()", trues, falses, pf, answer) == 1);//$
    assert(evaluate("aa|a", trues, falses, pf, answer) == 1);//$
    assert(evaluate("aa", trues, falses, pf, answer) == 1);
    assert(evaluate("&ab", trues, falses, pf, answer) == 1);//$
    assert(evaluate("|aa", trues, falses, pf, answer) == 1);
    assert(evaluate(")a", trues, falses, pf, answer) == 1);
    assert(evaluate("((((a))", trues, falses, pf, answer) == 1);
    assert(evaluate("a(|a)", trues, falses, pf, answer) == 1);
    assert(evaluate("a% | a", trues, falses, pf, answer) == 1);
    assert(evaluate("a!a!", trues, falses, pf, answer) == 1);
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
        //assert(evaluate("a&!(s|u&c|n)|!!!(s&u&n)", trues, falses, pf, answer) == 0  &&  pf == "asuc&n||!&su&n&!!!|" &&  answer);
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
