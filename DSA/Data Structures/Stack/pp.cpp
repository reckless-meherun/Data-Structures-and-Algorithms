#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int minAddToMakeValid(string paren)
{
    stack<char> s;
    int i = 0, count = 0;
    while (paren[i])
    {
        if (paren[i] == '(')
        {
            s.push('(');
        }
        else if (paren[i] == ')')
        {
            if (!s.empty())
            {
                if (s.top() == '(')
                {
                    s.pop();
                }
                else
                {
                    count++;
                }
            }
            else
            {
                count++;
            }
        }
        i++;
    }

    while (!s.empty())
    {
        s.pop();
        count++;
    }

    return count;
}

int main()
{
    freopen("input.in", "r", stdin);
    freopen("output.in", "w", stdout);
    string paren;
    cin >> paren;

    cout<<minAddToMakeValid(paren)<<endl;
    
    return 0;
}