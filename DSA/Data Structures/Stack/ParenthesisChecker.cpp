#include <bits/stdc++.h>
using namespace std;

bool check_paranthersis(string b);

int main()
{
    long long t;
    cin >> t;
    while (t--)
    {
        string brackets;
        cin >> brackets;

        if (check_paranthersis(brackets))
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }

    return 0;
}

bool check_paranthersis(string b)
{
    if (b == "" or b == " ")
        return true;

    stack<char> b_store;
    for (int i = 0; i < b.length(); i++)
    {
        if (b[i] == '(' or b[i] == '{' or b[i] == '[')
            b_store.push(b[i]);
        else
        {
            if (!b_store.empty())
            {
                if (b[i] == ')' and b_store.top() != '(')
                    return false;

                if (b[i] == '}' and b_store.top() != '{')
                    return false;

                else if (b[i] == ']' and b_store.top() != '[')
                    return false;

                b_store.pop();
            }
            else
                return false;
        }
    }
    return b_store.empty();
}