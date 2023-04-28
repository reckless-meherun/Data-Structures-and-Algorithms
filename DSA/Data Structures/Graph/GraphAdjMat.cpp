#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int adjMat[100][100];
int n, m; // n= number of vertices, m = number of edges
// the matrix will be nxn

void defineGraph()
{
    int u, v;

    for (int i = 0; i < m; i++)
    {
        cin >> u >> v;
        adjMat[u][v] = true;
        adjMat[v][u] = true;
    }
}

void addEdge(int u, int v)
{
    adjMat[u][v] = true;
    adjMat[v][u] = true;
}

void removeEdge(int u, int v)
{
    adjMat[u][v] = false;
    adjMat[v][u] = false;
}

void printGraph()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << adjMat[i][j] << " ";
        }
        cout << endl;
    }
    cout<<endl;
}

int main()
{
    freopen("input.in", "r", stdin);
    freopen("output.in", "w", stdout);

    cin >> n >> m;
    defineGraph();
    printGraph();
    addEdge(3,2);
    printGraph();
    removeEdge(0,1);
    printGraph();
    return 0;
}