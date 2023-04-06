// solution in a lengthy way

/** however the short solution is to find the pattern for n>4 and for n<=4, direct calculate by if else
 
 if(n%4==1 || n%4==2)
    ans=n+2;
 else if(n%4==3)
    ans=n-1;
 else
    ans=n+1;
    
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

long long check_precedence(string oper)
{
    if (oper == "/")
        return 4;
    if (oper == "*")
        return 4;
    if (oper == "+")
        return 3;
    if (oper == "-")
        return 3;
    return 0;
}

vector<string> infixToPostfix(vector<string> infix)
{

    stack<string> s;
    vector<string> postfix;
    // string postfix = "";

    for (long long i = 0; i < infix.size(); i++)
    {
        if (infix[i] == "(" or infix[i] == "{" or infix[i] == "[")
        {
            s.push(infix[i]);
        }
        else if (infix[i] == ")")
        {
            while (s.top() != "(")
            {
                // postfix += s.top();
                postfix.push_back(s.top());
                s.pop();
            }
            s.pop();
        }
        else if (infix[i] == "}")
        {
            while (s.top() != "{")
            {
                // postfix += s.top();
                postfix.push_back(s.top());
                s.pop();
            }
            s.pop();
        }
        else if (infix[i] == "]")
        {
            while (s.top() != "[")
            {
                // postfix += s.top();
                postfix.push_back(s.top());
                s.pop();
            }
            s.pop();
        }
        else if ((infix[i] >= "a" and infix[i] <= "z") or (infix[i] >= "A" and infix[i] <= "Z") or (infix[i] >= "0" and infix[i] <= "9"))
        {
            // postfix += infix[i];
            postfix.push_back(infix[i]);
            // postfix += " ";
            postfix.push_back(" ");
        }
        else
        {
            while (!s.empty() and (check_precedence(s.top()) >= check_precedence(infix[i])))
            {
                // postfix += s.top();
                postfix.push_back(s.top());
                s.pop();
            }
            s.push(infix[i]);
        }
    }

    while (!s.empty())
    {
        // postfix += s.top();
        postfix.push_back(s.top());
        s.pop();
    }
    return postfix;
}

string evaluatePostfix(vector<string> postfix)
{
    stack<string> s;
    for (long long i = 0; i < postfix.size(); i++)
    {
        if (postfix[i] == "+" or postfix[i] == "-" or postfix[i] == "*" or postfix[i] == "/")
        {

            while (!s.empty() and s.top() == " ")
                s.pop();

            string op1 = s.top();
            long long OP1 = atoi(op1.c_str());
            s.pop();

            while (s.top() == " ")
                s.pop();

            string op2 = s.top();
            long long OP2 = atoi(op2.c_str());
            s.pop();
            if (postfix[i] == "-")
            {
                s.push(to_string((OP2 - OP1)));
            }
            else if (postfix[i] == "/")
            {
                s.push(to_string((OP2 / OP1)));
            }
            else if (postfix[i] == "*")
            {
                s.push(to_string((OP2 * OP1)));
            }
            else
            {
                s.push(to_string((OP2 + OP1)));
            }
        }
        else
        {
            if (postfix[i] != " ") /** here is the problem with postfix[i] == " " */
                s.push(postfix[i]);
        }
    }
    return s.top();
}

vector<string> characterArrayToVectOfString(char c[])
{
    long long i = 0;
    vector<string> v;
    string temp = "";
    while (c[i] != ' ' and i < strlen(c))
    {
        temp += c[i++];
        if (c[i] == ' ')
        {
            v.push_back(temp);
            i++;
            temp = "";
        }
    }
    return v;
}

long long clumsy(long long n)
{
    vector<string> infix;

    for (long long j = n, i = 1; j >= 1; j--, i++)
    {
        infix.push_back(to_string(j));
        if (j != 1)
        {
            if (i % 4 == 1)
            {
                infix.push_back("*");
            }
            else if (i % 4 == 2)
            {
                infix.push_back("/");
            }
            else if (i % 4 == 3)
            {
                infix.push_back("+");
            }
            else if (i % 4 == 0)
            {
                infix.push_back("-");
            }
        }
    }
    vector<string> s = infixToPostfix(infix);
    // for (auto v : infix)
    // {
    //     cout << v;
    // }
    // cout << endl;
    string ans = evaluatePostfix(s);
    return atoi(ans.c_str());
}

long long main()
{
    long long n;
    cin >> n;
    cout << clumsy(n);
    return 0;
}