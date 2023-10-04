#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int dp[1010][1010], vis[1010][1010];
int danger[1010][1010] = {
    {3, 2, 5, 4, 8},
    {5, 7, 5, 6, 1},
    {4, 4, 6, 2, 3},
    {2, 8, 9, 5, 8}};
int reDanger[2 * 1010][2 * 1010];

void printBestPath(int i, int j, int n)
{
    if (i == n) // to print the starting point
        cout << reDanger[i][j] << " ";
    if (i == 0 or j == 0)
        return;
    else if (dp[i - 1][j - 1] < dp[i - 1][j] and dp[i - 1][j - 1] < dp[i - 1][j + 1])
    {
        cout << reDanger[i - 1][j - 1] << " ";
        printBestPath(i - 1, j - 1, n);
    }
    else if (dp[i - 1][j] < dp[i - 1][j - 1] and dp[i - 1][j] < dp[i - 1][j + 1])
    {
        cout << reDanger[i - 1][j] << " ";
        printBestPath(i - 1, j, n);
    }
    else if (dp[i - 1][j + 1] < dp[i - 1][j - 1] and dp[i - 1][j + 1] < dp[i - 1][j])
    {
        cout << reDanger[i - 1][j + 1] << " ";
        printBestPath(i - 1, j + 1, n);
    }
}

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

int climbRocksBottomUp(int n, int m)
{
    // initialize
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

    // dp calculation
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            dp[i][j] = reDanger[i][j] + min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i - 1][j + 1]));
        }
    }

    // printDPArray(n, m);

    // find the minimum of the last row
    int ans = INT_MAX;
    int final_x = n, final_y = m;
    for (int j = 1; j <= m; j++)
    {
        if (dp[n][j] < ans)
        {
            ans = min(ans, dp[n][j]);
            final_y = j;
        }
    }
    cout << "The best path to climb the rocks : ";
    printBestPath(final_x, final_y, n); // pass n to print the starting  point
    cout << endl
         << "Minimum path Danger : ";
    return ans;
}

int climbRocksTopDown(int n, int m)
{
    if (n == 0 or m == 0)
        return 0;
    if (vis[n][m])
        return dp[n][m];
    int i = 1, j = 1;
    for (j = 1; j <= m; j++)
    {
        dp[n][j] = reDanger[n][j] + min(climbRocksTopDown(n - 1, j - 1), min(climbRocksTopDown(n - 1, j), climbRocksTopDown(n - 1, j + 1)));
    }
    dp[n][m] = dp[n][j - 1];
    return dp[n][m];
}

int main()
{
    cout << climbRocksBottomUp(4, 5);
    cout << endl;
    cout<< climbRocksTopDown(4,5);
    return 0;
}