#include <bits/stdc++.h>
using namespace std;

int main()
{
    string postfix;
    stack<string> infix;

    cin >> postfix;
    for (int i = 0; i < postfix.length(); i++)
    {
        if ((postfix[i] >= 'A' and postfix[i] <= 'Z') or (postfix[i] >= 'a' and postfix[i] <= 'z') or (postfix[i] >= '0' and postfix[i] <= '9'))
        {
            infix.push(string(1, postfix[i])); //converting a single character to a string
            // string class has a constructor
            // that allows us to specify size of
            // string as first parameter and character
            // to be filled in given size as second
            // parameter.
        }
        else
        {
            string operand_one = infix.top();
            infix.pop();
            string operand_two = infix.top();
            infix.pop();
            char operator_between = postfix[i];

            string need_to_push = "(" + operand_two + operator_between + operand_one + ")";
            infix.push(need_to_push);
        }
    }

    cout << infix.top() << endl;

    return 0;
}