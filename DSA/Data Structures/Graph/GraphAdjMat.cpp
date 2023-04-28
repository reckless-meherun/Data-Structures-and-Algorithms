#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int adjMat[100][100];
int vertices, edges; 

void defineGraph()
{
    int u, v;

    for (int i = 0; i < edges; i++)
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
    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < vertices; j++)
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

    cin >> vertices >> edges;
    defineGraph();
    printGraph();
    addEdge(3,2);
    printGraph();
    removeEdge(0,1);
    printGraph();
    return 0;
}