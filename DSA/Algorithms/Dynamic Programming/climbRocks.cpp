#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int dp[1010][1010], vis[1010][1010], rockGrid[1010][1010];
#define inf 1e5

int climbRocks(int x, int y)
{
    if (x == 0 and y == 0)
        return rockGrid[0][0];
    if (x < 0 or y < 0)
        return -inf;

    if (vis[x][y])
        return dp[x][y];

    vis[x][y] = 1;
    int left = climbRocks(x - 1, y);
    int up = climbRocks(x, y - 1);

    dp[x][y] = rockGrid[x][y] + max(left, up);
    return dp[x][y];
}

void inputRock(int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> rockGrid[i][j];
           // cout<<rockGrid[i][j]<<" ";
        }
        //cout<<endl;
    }
}

int main()
{
    int n, m;
    cin>>n>>m;
    inputRock(n, m);
    cout<<climbRocks(3,4);
    return 0;
}