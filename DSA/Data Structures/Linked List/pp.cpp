#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

string smallestNumber(string pattern)
{
    string num_string = "";
    int i;
    for (i = 0; i < pattern.length(); i++)
    {
        num_string = num_string + to_string(i + 1);
    }
    num_string = num_string + to_string(i + 1);
    i = 0;
    for (int i = 0; i < pattern.length(); )
    {
        string y = "";
        for (int k = 0; pattern[k] != 'D'; k++)
        {
            y += pattern[k];
        }

        if (pattern[i] == 'D')
        {
            stack<char> rev;
            int j = i;
            int st = j;
            while (j < pattern.length() and pattern[j] != 'I')
            {
                rev.push(pattern[j]);
                j++;
            }
            string x = "";
            while (!rev.empty())
            {
                x += rev.top();
                rev.pop();
            }

            int ed = j;
            reverse(num_string.begin() + st, num_string.begin() + ed + 1);
            i = j;
        }
        else
            i++;
    }
    return num_string;
}

int main()
{
    freopen("input.in", "r", stdin);
    freopen("output.in", "w", stdout);
    string pat;
    cin >> pat;
    cout << smallestNumber(pat) << endl;

    return 0;
}