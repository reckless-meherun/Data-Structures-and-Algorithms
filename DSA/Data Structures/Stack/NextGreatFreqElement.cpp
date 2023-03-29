#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void NGF(int num[], int n)
{
    map<int, int> freq;

    for (int i = 0; i < n; i++)
    {
        freq[num[i]]++;
    }
    
    int f[10000];
    for (int i = 0; i < n; i++)
    {
        f[i] = freq[num[i]];
    }

    stack<int> s;
    s.push(0);
    vector<int> count(n, 0);
    for (int i = 1; i < n; i++)
    {
        while (!s.empty() and f[i] > f[s.top()])
        {
            count[s.top()] = num[i];
            s.pop();
        }
        s.push(i);
    }
    
    while (!s.empty())
    {
        count[s.top()] = -1;
        s.pop();
    }

    for (auto v : count)
    {
        cout << v << " ";
    }
}

int main()
{
    freopen("input.in", "r", stdin);
    freopen("output.in", "w", stdout);
    int n;
    cin >> n;
    int num[10000];
    for (int i = 0; i < n; i++)
    {
        cin >> num[i];
    }
    NGF(num, n);
    return 0;
}