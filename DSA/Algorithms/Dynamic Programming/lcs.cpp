#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

#define fastio                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);
#define MULTIPLE_TEST \
    int t;            \
    cin >> t;         \
    while (t--)
#define notun '\n'
#define vi vector<int>
#define pb(a) push_back(a)
#define all(x) x.begin(), x.end()
#define forV(x, arr) for (auto x : arr)
#define forP(a, b, arr) for (auto [a, b] : arr)

// local array size = 1e5, global = 1e8
// int = 1e9, long long = 1e18
//  1 sec = 1e7 ~ 1e8

const int N = 1e7 + 10;
const int mod = 1e9 + 7;

int lcs(string &s1, string &s2)
{
    int n1 = s1.size(), n2 = s2.size();
    vector<vector<int>> dp(n1 + 1, vector<int>(n2 + 1, 0));

    vector<vector<int>> path(n1 + 1, vector<int>(n2 + 1, 0));

    for (int i = 1; i <= n1; i++)
    {
        for (int j = 1; j <= n2; j++)
        {
            if (s1[i - 1] == s2[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                path[i][j] = 2;
            }
            else
            {
                if (dp[i - 1][j] > dp[i][j - 1])
                {
                    dp[i][j] = dp[i - 1][j];
                    path[i][j] = 1;
                }
                else
                {
                    dp[i][j] = dp[i][j - 1];
                    path[i][j] = 0;
                }
            }
        }
    }

    string ans;
    int i = n1, j = n2;

    while (i >= 0 && j >= 0)
    {
        switch (path[i][j])
        {
        case 0:
            j--;
            break;
        case 1:
            i--;
            break;
        case 2:
            ans.push_back(s1[i - 1]);
            i--;
            j--;
            break;
        }
    }
    reverse(all(ans));
    cout << ans << notun;

    return dp[n1][n2];
}

int main()
{
    fastio;
    string s1 = "abcbda";
    string s2 = "bdcaba";
    cout << lcs(s1, s2);

    return 0;
}