#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool canGo(int pos[][1000], int x, int y, int m, int n)
{
    if (x < m and y < n and pos[x][y] == 1)
    {
        return true;
    }
    return false;
}

bool ratinMaze(int arr[][1000], int x, int y, int m, int n, int sol[][1000])
{
    if (x == m - 1 and y == n - 1)
    {
        sol[x][y] = 1;
        return true;
    }
    if (canGo(arr, x, y, m, n))
    {
        sol[x][y] = 1;
        if (ratinMaze(arr, x + 1, y, m, n, sol))
        {
            return true;
        }
        if (ratinMaze(arr, x, y + 1, m, n, sol))
        {
            return true;
        }
        sol[x][y] = 0; // backtracking
        return false;
    }
    return false;
}

int main()
{
    freopen("input.in", "r", stdin);
    freopen("output.in", "w", stdout);
    int path[1000][1000];
    int m, n;
    cin >> m >> n;
    
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin>>path[i][j];
        }
    }

    int sol[1000][1000];
    memset(sol, 0, sizeof(int));
    ratinMaze(path, 0, 0, m, n, sol);

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout<<sol[i][j]<<" ";
        }
        cout<<endl;
    }

    return 0;
}