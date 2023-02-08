//almost same as the infix to postfix except that u need to replace '(' with ')' 
//and vice versa. At the end, just the reverse the string postfix
//when u r done with all these 4, u cam do any conversion u want

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

    string prefix="";
    
    for (int i = infix.length()-1; i >=0; i--)
    {
        if (infix[i] == ')')
        {
            s.push(')');
        }
        else if (infix[i] == '(')
        {
            while(s.top()!=')')
            {
                prefix += s.top();
                s.pop();
            }
            s.pop();
        }
        else if ((infix[i] >= 'a' and infix[i] <= 'z') or (infix[i] >= 'A' and infix[i] <= 'Z') or (infix[i] >= '0' and infix[i] <= '9'))
        {
            prefix += infix[i];
        }
        else
        {        
            while (!s.empty() and (check_precedence(s.top())>=check_precedence(infix[i])))
            {
                prefix += s.top();
                s.pop();
            }
            s.push(infix[i]);            
        }
    }

    while(!s.empty())
    {
        prefix += s.top();
        s.pop();
    }

    reverse(prefix.begin(), prefix.end());
    cout<<prefix<<endl;

    return 0;
}