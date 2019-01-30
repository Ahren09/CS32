#include <stdio.h>
#include <string>
#include <stack>
#include <cctype>

using namespace std;



int evaluate(string infix, const Set& trueValues, const Set& falseValues, string& postfix, bool& result)
{
    int len=infix.size();
    int i=0;
    stack<char> s;
    
    while(i<len)
    {
        char ch=infix[i];
        if(!trueValues.contains(ch) || !falseValues.contains(infix[i]))
            return false;
        
        switch(ch)
        {
            case '(':
                s.push('(');
                break;
            case ')':
                while(s.top()!=')')
                {
                    postfix+=s.top();
                    s.pop();
                }
                s.pop();
            
            case '!':
            case '&':
            case '|':
                if(!s.empty() && )
                {
                    postfix+=s.top();
                    s.pop();
                }
                s.push(ch);
            
        }
        
        
        
        
    }
    while(!s.empty())
    {
        postfix+=s.top();
        s.pop();
    }
    
    
}
