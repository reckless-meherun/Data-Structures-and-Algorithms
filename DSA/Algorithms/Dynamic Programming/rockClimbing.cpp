#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int dp[1010][1010], vis[1010][1010];
int danger[1010][1010] = {
    {3, 2, 5, 4, 8},
    {5, 7, 5, 6, 1},
    {4, 4, 6, 2, 3},
    {2, 8, 9, 5, 8}};

void printDPArray(int n, int m)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }
}

int climbRocks(int n, int m)
{
    int reDanger[2 * n][2 * m];

    //initialize
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= m + 1; j++)
        {
            if (j == 0 or j == m + 1)
            {
                reDanger[i][j] = INT_MAX;
                dp[i][j] = INT_MAX;
            }
            else if (i == 0)
                reDanger[i][j] = 0;

            else
                reDanger[i][j] = danger[i - 1][j - 1];
        }
    }

    //dp calculation
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            dp[i][j] = reDanger[i][j] + min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i - 1][j + 1]));
        }
    }

    //printDPArray(n, m);

    //find the minimum of the last row
    int ans = INT_MAX;
    for (int j = 1; j <= m; j++)
    {
        ans = min(ans, dp[n][j]);
    }
    return ans;
}

int main()
{
    cout << climbRocks(4, 5);
    return 0;
}