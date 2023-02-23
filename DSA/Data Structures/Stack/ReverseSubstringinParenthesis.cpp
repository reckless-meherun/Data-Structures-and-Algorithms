#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

string reverseParentheses(string s)
{
    s = "(" + s + ")";
    stack<string> rev;
    string ans = "";
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] != ')')
        {
            string a(1, s[i]);
            rev.push(a);
        }
        else
        {
            ans = "";
            while (!rev.empty() and rev.top() != "(")
            {
                ans += rev.top();
                rev.pop();
            }
            if (rev.top() == "(")
                rev.pop();

            if (!rev.empty())
            {
                reverse(ans.begin(), ans.end());
                rev.push(ans);
            }
        }
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

int main()
{
    freopen("input.in", "r", stdin);
    freopen("output.in", "w", stdout);
    string line;
    cin >> line;
    cout << reverseParentheses(line) << endl;
    return 0;
}