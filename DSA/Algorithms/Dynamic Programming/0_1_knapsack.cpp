#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int weight[3] = {10, 20, 30};
int profit[3] = {60, 100, 120};

int dp[1010][1010], vis[1010][1010];

int knapsackProfit(int i, int W)
{
    if (W < 0)
        return INT_MIN;
    if (i < 0)
        return 0;

    if (vis[i][W])
        return dp[i][W];
    vis[i][W] = 1;

    // if consider i
    int ans1 = profit[i] + knapsackProfit(i - 1, W - weight[i]);

    // if do not consider i
    int ans2 = knapsackProfit(i - 1, W);

    dp[i][W] = max(ans1, ans2);

    return dp[i][W];
}

int main()
{
    memset(vis, 0, sizeof(vis));
    cout<<knapsackProfit(2, 50);
    return 0;
}