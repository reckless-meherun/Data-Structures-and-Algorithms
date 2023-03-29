#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool validateStackSequences(vector<int> &pushed, vector<int> &popped)
{
    stack<int> s;
    int i = 0, j = 0;
    for (; i < pushed.size();)
    {
        s.push(pushed[i]);
        i++;
        while (!s.empty() and popped[j] == s.top())
        {
            s.pop();
            j++;
        }
    }

    while (!s.empty())
    {
        if (s.top() != popped[j])
        {
            return false;
        }
        s.pop();
        j++;
    }
    return true;
}

int main()
{
    freopen("input.in", "r", stdin);
    freopen("output.in", "w", stdout);
    int n;
    cin >> n;
    vector<int> pushed(n);
    vector<int> popped(n);
    for (int i = 0; i < n; i++)
    {
        cin >> pushed[i];
    }
    for (int i = 0; i < n; i++)
    {
        cin >> popped[i];
    }
    if (validateStackSequences(pushed, popped))
        cout << "true" << endl;
    else
        cout << "false" << endl;
    return 0;
}