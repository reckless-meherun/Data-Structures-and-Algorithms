#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int dp[1010], vis[1010], preV[1010];
//int seq[1010] = {9, 2, 5, 3, 7, 11, 8, 10, 13, 6};
int seq[1010] = {50, 3, 10, 7, 40, 80};
int n = 6;

void reset()
{
    for (int i = 0; i < 1010; i++)
    {
        dp[i] = 0;
        vis[i] = 0;
    }
}

void printLis(int i)
{
    if (i == 0)
        return;
    printLis(preV[i]);
    cout << seq[i] << " ";
}

int lisBottomUp(int n)
{
    preV[0] = -1;
    int lastIndex = n - 1;
    for (int i = 0; i < n; i++)
        dp[i] = 1; // even if all the other elements are greater than the last element, there is a valid sequence of length 1 containing that last element only
    int ans = 0;   // when there the sequence is empty
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (seq[j] < seq[i])
            {
                if (dp[i] < (dp[j] + 1))
                {
                    dp[i] = dp[j] + 1;
                    preV[i] = j;
                }
            }
        }
        if (ans < dp[i])
        {
            ans = dp[i];
            lastIndex = i;
        }
    }
    printLis(lastIndex);
    cout<<endl;
    return ans;
}

int lisTopDownRec(int lastIndx) // gets the length of the LIS if the ending number if seq[lastIndex]
{
    if (vis[lastIndx])
        return dp[lastIndx];
    vis[lastIndx] = 1;

    int ans = 1;

    for (int j = 0; j < lastIndx; j++)
    {
        if (seq[j] < seq[lastIndx])
        {
            ans = max(ans, 1 + lisTopDownRec(j));
        }
    }
    dp[lastIndx] = ans;
    return dp[lastIndx];
}

int lisTopDown(int n)
{
    int ans = 0;                // when there the sequence is empty
    for (int i = 0; i < n; i++) // because we need to calculate for all index considering the last index
        ans = max(ans, lisTopDownRec(i));
    return ans;
}

int main()
{
    cout << lisTopDown(n);
    cout << endl;
    reset();
    cout << lisBottomUp(n);
    return 0;
}