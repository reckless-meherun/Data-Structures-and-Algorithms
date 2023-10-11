#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define inf 1e8

class matrix
{
public:
    int n, m;
    int mat[1010][1010];
};

int dp[1010][1010], vis[1010][1010];
int chain[1010];
int par[1010][1010];
string infix = "";
bool bottomUp = false;

int mcmBottomUp(int chainLen)
{
    bottomUp = true;
    for (int l = 2; l < chainLen; l++)
    {
        for (int i = 1; i < chainLen - l + 1; i++)
        {
            int j = i + l - 1;
            dp[i][j] = inf;
            for (int k = i; k < j; k++)
            {
                int q = dp[i][k] + dp[k + 1][j] + chain[i - 1] * chain[k] * chain[j];
                if (q < dp[i][j])
                {
                    dp[i][j] = q;
                    par[i][j] = k;
                }
            }
        }
    }
    return dp[1][chainLen - 1];
}

void printParenthesis(int i, int j)
{
    if (i == j)
    {
        // cout << (char)(i + 64);
        infix += (char)(i + 64);
        return;
    }
    else
    {
        // cout << "(";
        infix += "(";
        printParenthesis(i, par[i][j]);
        printParenthesis(par[i][j] + 1, j);
        // cout << ")";
        infix += ")";
    }
}

int mcmTopDownRec(int i, int j)
{
    if (i == j)
        return 0;

    if (vis[i][j])
        return dp[i][j];
    vis[i][j] = 1;

    dp[i][j] = inf;
    for (int k = i; k < j; k++)
    {
        int q = mcmTopDownRec(i, k) + mcmTopDownRec(k + 1, j) + chain[i - 1] * chain[k] * chain[j];
        if (q < dp[i][j])
        {
            dp[i][j] = q;
            par[i][j] = k;
        }
    }
    return dp[i][j];
}

int mcmTopDown(int chainLen)
{
    return mcmTopDownRec(1, chainLen - 1);
}

void printDPArray(int n)
{
    cout <<endl<< "DP Array" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }
}

void printTrackingArray(int n)
{
    cout << "Tracking Array" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << par[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{
    int chainLen;
    cin >> chainLen;
    for (int i = 0; i < chainLen; i++)
    {
        cin >> chain[i];
    }
    int cost = mcmBottomUp(chainLen);
    printParenthesis(1, chainLen - 1);
    cout << infix << endl;
    cout << "Optimal cost is : " << cost << endl;
    if(bottomUp)
    {
        printDPArray(chainLen);
        cout << endl;
        printTrackingArray(chainLen);
    }

    return 0;
}
