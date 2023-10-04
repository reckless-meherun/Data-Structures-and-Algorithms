#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int dp[1010][1010], vis[1010][1010];
string string_a = "BD";
string string_b = "ABCD";

enum direcction
{
    LEFT,
    UP,
    UPDIAG
};
direcction dir[1010][1010];

void reset()
{
    for (int i = 0; i < 1010; i++)
    {
        for (int j = 0; j < 1010; j++)
        {
            dp[i][j] = 0;
            vis[i][j] = 0;
        }
    }
}

void printLCS(int i, int j)
{
    if (i == 0 or j == 0)
        return;
    else if (dir[i][j] == UPDIAG)
    {
        printLCS(i - 1, j - 1);
        cout << string_a[i-1];
    }
    else if (dir[i][j] == UP)
        printLCS(i - 1, j);
    else
        printLCS(i, j - 1);
}

/** adding extra empty rows and columns */
int lcsBottomUp(int len_a, int len_b) // length
{
    for (int i = 0; i <= len_a; i++)
    {
        for (int j = 0; j <= len_b; j++)
        {
            if (i == 0 || j == 0)
                dp[i][j] = 0;
            else if (string_a[i - 1] == string_b[j - 1])
            {
                dp[i][j] = 1 + dp[i - 1][j - 1];
                dir[i][j] = UPDIAG;
            }
            else
            {
                if (dp[i - 1][j] > dp[i][j - 1])
                {
                    dp[i][j] = dp[i - 1][j];
                    dir[i][j] = UP;
                }
                else
                {
                    dp[i][j] = dp[i][j - 1];
                    dir[i][j] = LEFT;
                }
            }
        }
    }
    cout<<"lcs : ";
    printLCS(len_a, len_b);
    cout<<endl;
    cout<<"length of lcs : ";
    return dp[len_a][len_b];
}

/** not adding extra empty rows and columns */

// int lcsBottomUp(int len_a, int len_b) // length
// {
//     for (int i = 0; i < len_a; i++)
//     {
//         for (int j = 0; j < len_b; j++)
//         {
//             if (string_a[i] == string_b[j])
//             {
//                 if (i == 0 or j == 0)
//                     dp[i][j] = 1;
//                 else
//                     dp[i][j] = 1 + dp[i - 1][j - 1];
//             }
//             else
//             {
//                 if (i == 0 and j != 0)
//                     dp[i][j] = dp[i][j - 1];
//                 else if (i != 0 and j == 0)
//                     dp[i][j] = dp[i - 1][j];
//                 else if (i == 0 and j == 0)
//                     dp[i][j] = 0;
//                 else
//                     dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
//             }
//         }
//     }

//     for (int i = 0; i < len_a; i++)
//     {
//         for (int j = 0; j < len_b; j++)
//         {
//             cout << dp[i][j] << " ";
//         }
//         cout << endl;
//     }

//     return dp[len_a - 1][len_b - 1];
// }

int lcsTopDown(int indx_a, int indx_b) // last index len-1
{
    if (indx_a == -1 or indx_b == -1)
        return 0;
    if (vis[indx_a][indx_b])
        return dp[indx_a][indx_b];
    vis[indx_a][indx_b] = 1;

    int a = 0, b = 0, c = 0;
    if (string_a[indx_a] == string_b[indx_b])
        a = 1 + lcsTopDown(indx_a - 1, indx_b - 1);
    else
    {
        b = lcsTopDown(indx_a, indx_b - 1);
        c = lcsTopDown(indx_a - 1, indx_b);
    }
    dp[indx_a][indx_b] = max(a, max(b, c));
    return dp[indx_a][indx_b];
}

int main()
{
    cout << lcsTopDown(string_a.size() - 1, string_b.size() - 1);
    cout << endl;
    reset();
    cout << lcsBottomUp(string_a.size(), string_b.size());
    return 0;
}