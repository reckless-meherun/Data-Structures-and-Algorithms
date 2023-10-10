#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define inf 1e5

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

int mcmBottomUp(int chainLen)
{
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
        //cout << "(";
        infix += "(";
        printParenthesis(i, par[i][j]);
        printParenthesis(par[i][j] + 1, j);
        //cout << ")";
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

void countResult()
{
    stack<matrix> st_mat;
    stack<char> st;
    for (int i = 0; i < infix.size(); i++)
    {
        if (infix[i] == '(')
            st.push('(');
        else if (infix[i] == ')')
        {
            st.pop();
            matrix B = st_mat.top();
            st_mat.pop();
            matrix A = st_mat.top();
            st_mat.pop();

            matrix C;
            C.n = A.n;
            C.m = B.m;

            for (int k = 0; k < C.n; k++)
            {
                for (int j = 0; j < C.m; j++)
                {
                    C.mat[k][j] = 0;
                }
            }
            for (int j = 0; j < C.n; j++)
            {
                for (int k = 0; k < C.m; k++)
                {
                    for (int l = 0; l < B.n; l++)
                    {
                        C.mat[j][k] += A.mat[j][l] * B.mat[l][k];
                    }
                }
            }
            st_mat.push(C);
        }
        else
        {
            int x = infix[i] - 65;
            cout << x << "th matrix : \n";
            int p = chain[x];
            int q = chain[x + 1];

            matrix xx;
            xx.n = p;
            xx.m = q;

            for (int j = 0; j < p; j++)
            {
                for (int k = 0; k < q; k++)
                {
                    xx.mat[j][k] = rand() % 5;
                    cout << xx.mat[j][k]<<" ";
                }
                cout << "\n";
            }
            st_mat.push(xx);
        }
    }
    matrix lastMat = st_mat.top();
    cout<<"\nResult of the multiplication : \n";
    for (int i = 0; i < lastMat.n; i++)
    {
        for (int j = 0; j < lastMat.m; j++)
        {
            printf("%d ", lastMat.mat[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int chainLen;
    cin>>chainLen;
    for(int i=0; i<chainLen; i++)
    {
        cin>>chain[i];
    }
    cout << mcmTopDown(chainLen);
    cout << endl;
    printParenthesis(1, chainLen - 1);
    cout << endl;
    cout << infix << endl;
    countResult();
    return 0;
}
