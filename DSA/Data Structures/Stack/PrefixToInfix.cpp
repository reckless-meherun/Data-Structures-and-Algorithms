#include <bits/stdc++.h>
using namespace std;

int main()
{
    string prefix;
    stack<string> infix;

    cin >> prefix;
    for (int i = prefix.length() - 1; i >= 0; i--)
    {
        if ((prefix[i] >= 'A' and prefix[i] <= 'Z') or (prefix[i] >= 'a' and prefix[i] <= 'z') or (prefix[i] >= '0' and prefix[i] <= '9'))
        {
            infix.push(string(1, prefix[i])); //converting a single character to a string
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
            char operator_between = prefix[i];

            string need_to_push = "(" + operand_one + operator_between + operand_two + ")";
            infix.push(need_to_push);
        }
    }

    cout << infix.top() << endl;

    return 0;
}