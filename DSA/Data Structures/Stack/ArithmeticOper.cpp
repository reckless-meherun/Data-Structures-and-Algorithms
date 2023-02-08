#include <bits/stdc++.h>
using namespace std;

int check_precedence(char oper)
{
    if (oper == '/')
        return 4;
    if (oper == '*')
        return 4;
    if (oper == '+')
        return 3;
    if (oper == '-')
        return 3;
    return 0;
}

string Infix_To_Postfix(char infix[])
{
    stack<char> s;
    string postfix = "";
    string tmp;
    int num;
    for (int i = 0; i < strlen(infix); i++)
    {
        if (infix[i] == ' ')
        {
            postfix += tmp;
            tmp = "";
            postfix += ' ';
            continue;
        }
        if (infix[i] == '(' or infix[i] == '{' or infix[i] == '[')
        {
            tmp = "";
            s.push(infix[i]);
        }
        else if (infix[i] == ')')
        {
            tmp = "";
            while (s.top() != '(')
            {
                postfix += s.top();
                s.pop();
            }
            s.pop();
        }
        else if (infix[i] == '}')
        {
            tmp = "";
            while (s.top() != '{')
            {
                postfix += s.top();
                s.pop();
            }
            s.pop();
        }
        else if (infix[i] == ']')
        {
            tmp = "";
            while (s.top() != '[')
            {
                postfix += s.top();
                s.pop();
            }
            s.pop();
        }
        else if (infix[i] >= '0' and infix[i] <= '9')
        {
            if (tmp != "")
            {
                num = stoi(tmp);
                num = num * 10 + (infix[i]-'0');
                tmp = to_string(num);
            }
            else
                tmp += infix[i];
        }
        else
        {
            tmp = "";
            while (!s.empty() and (check_precedence(s.top()) >= check_precedence(infix[i])))
            {
                postfix += s.top();
                s.pop();
            }
            s.push(infix[i]);
        }
    }

    while (!s.empty())
    {
        postfix += s.top();
        s.pop();
    }
    return postfix;
}

string do_algebra(string postfix)
{
    stack<string> ans;
    string tmp="";
    int num;

    for (int i = 0; i < postfix.length(); i++)
    {
        if (postfix[i] == ' ')
        {
            ans.push(tmp);
            tmp = "";
            continue;
        }
        else if (postfix[i] >= '0' and postfix[i] <= '9')
        {
            if (tmp != "")
            {
                num = stoi(tmp);
                num = num * 10 + (postfix[i]-'0');
                tmp = to_string(num);
            }
            else
                tmp += postfix[i];
        }
        else
        {
            tmp = "";
            char optr = postfix[i];
            string operand_one = ans.top();
            int num_one = stoi(operand_one);
            ans.pop();
            string operand_two = ans.top();
            int num_two = stoi(operand_two);
            ans.pop();
            int res;
            if (optr == '/')
            {
                res = num_one/num_two;
            }
            else if (optr == '*')
            {
                res = num_one*num_two;
            }
            else if (optr == '+')
            {
                res = num_one+num_two;
            }
            else if (optr == '-')
            {
                res = num_one-num_two;
            }
            tmp = to_string(res);
        }
    }
    ans.push(tmp);
    return ans.top();
}

int main()
{
    char infix[100];
    scanf("%[^\n]", infix);

    string postfix = Infix_To_Postfix(infix);
    cout<<postfix<<endl;
   
    string ans = do_algebra(postfix);
    cout<<ans<<endl;

    return 0;
}