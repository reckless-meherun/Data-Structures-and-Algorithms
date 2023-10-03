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

enum
{
    LEFT,
    MIDDLE,
    RIGHT
};

const int N = 1e7 + 10;
const int mod = 1e9 + 7;
vector<vector<int>> wall;
vector<vector<int>> path;

int rock_climbing()
{

    vector<vector<int>> dp = wall;
    for (int i = 1; i < dp.size(); i++)
    {
        for (int j = 0; j < dp[0].size(); j++)
        {
            int temp = dp[i - 1][j];
            path[i][j] = MIDDLE;

            if (j > 0)
            {
                if (temp > dp[i - 1][j - 1])
                {
                    temp = dp[i - 1][j - 1];
                    path[i][j] = LEFT;
                }
            }
            if (j < dp[0].size() - 1)
            {
                if (temp > dp[i - 1][j + 1])
                {
                    temp = dp[i - 1][j + 1];
                    path[i][j] = RIGHT;
                }
            }

            dp[i][j] += temp;
        }
    }
    int i = dp.size() - 1;
    int j = min_element(all(dp[dp.size() - 1])) - dp[dp.size() - 1].begin();

    while (i >= 0)
    {
        cout << wall[i][j] << " ";
        switch (path[i][j])
        {
        case LEFT:
            i--;
            j--;
            break;
        case RIGHT:
            i--;
            j++;
            break;

        default:
            i--;
            break;
        }
    }
    cout << notun;

    return *min_element(all(wall[wall.size() - 1]));
}

int main()
{

    fastio

        int n,
        m;
    cin >> n >> m;

    wall.assign(n, vector<int>(m));
    path.assign(n, vector<int>(m));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> wall[i][j];
        }
    }

    cout << rock_climbing();

    return 0;
}