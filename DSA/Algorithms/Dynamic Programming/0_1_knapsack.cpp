#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int weight[1010] = {2, 3, 4, 5};
int profit[1010] = {1, 2, 5, 6};

int dp[1010][1010], vis[1010][1010];

int knapsackBottomUp(int numObject, int maxCapacity)
{
    for (int i = numObject; i > 0; i--)
    {
        weight[i] = weight[i - 1];
        profit[i] = profit[i - 1];
    }
    weight[0] = 0;
    profit[0] = 0;

    for (int object = 0; object <= numObject; object++)
    {
        for (int capacity = 0; capacity <= maxCapacity; capacity++)
        {
            if (object == 0 or capacity == 0)
                dp[object][capacity] = 0;
            else if (capacity >= weight[object])
                dp[object][capacity] = max(dp[object - 1][capacity], profit[object] + dp[object - 1][capacity - weight[object]]);
            else
                dp[object][capacity] = dp[object - 1][capacity];
        }
    }
    return dp[numObject][maxCapacity];
}

int knapsackTopDown(int i, int W)
{
    if (W < 0)
        return INT_MIN;
    if (i < 0)
        return 0;

    if (vis[i][W])
        return dp[i][W];
    vis[i][W] = 1;

    // if consider i
    int ans1 = profit[i] + knapsackTopDown(i - 1, W - weight[i]);

    // if do not consider i
    int ans2 = knapsackTopDown(i - 1, W);

    dp[i][W] = max(ans1, ans2);

    return dp[i][W];
}

int main()
{
    memset(vis, 0, sizeof(vis));
    cout << knapsackTopDown(4-1, 8);
    cout<<endl;
    cout<<knapsackBottomUp(4, 8);
    return 0;
}