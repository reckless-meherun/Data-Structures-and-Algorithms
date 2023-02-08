#include <bits/stdc++.h>
using namespace std;

int check_precedence(char oper)
{
    if(oper=='/')
        return 4;
    if(oper=='*')
        return 4;
    if(oper=='+')
        return 3;
    if(oper=='-')
        return 3;
    return 0;
}

int main()
{
    stack<char> s;
    string infix;
    cin >> infix;

    string postfix="";
    
    for (int i = 0; i < infix.length(); i++)
    {
        if (infix[i] == '(' or infix[i] == '{' or infix[i] == '[')
        {
            s.push(infix[i]);
        }
        else if (infix[i] == ')')
        {
            while(s.top()!='(')
            {
                postfix += s.top();
                s.pop();
            }
            s.pop();
        }
        else if (infix[i] == '}')
        {
            while(s.top()!='{')
            {
                postfix += s.top();
                s.pop();
            }
            s.pop();
        }
        else if (infix[i] == ']')
        {
            while(s.top()!='[')
            {
                postfix += s.top();
                s.pop();
            }
            s.pop();
        }
        else if ((infix[i] >= 'a' and infix[i] <= 'z') or (infix[i] >= 'A' and infix[i] <= 'Z') or (infix[i] >= '0' and infix[i] <= '9'))
        {
            postfix += infix[i];
        }
        else
        {        
            while (!s.empty() and (check_precedence(s.top())>=check_precedence(infix[i])))
            {
                postfix += s.top();
                s.pop();
            }
            s.push(infix[i]);            
        }
    }

    while(!s.empty())
    {
        postfix += s.top();
        s.pop();
    }

    cout<<postfix<<endl;

    return 0;
}