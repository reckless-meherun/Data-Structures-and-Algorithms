#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class graph
{
    int vertices;
    int edges;
    bool directed;
    vector<list<int>> adjList;

    int *prev;
    int *distance;

public:
    graph(int vertices, int edges, bool ifDirected)
    {
        this->vertices = vertices;
        this->edges = edges;
        adjList.resize(vertices);
        directed = ifDirected;

        prev = new int[vertices + 1];
        distance = new int[vertices + 1];
    }

    void defineGraph()
    {
        for (int i = 0; i < edges; i++)
        {
            int u, v;
            cin >> u >> v;
            addEdge(u, v);
        }
    }

    void addEdge(int u, int v)
    {
        ;
        if (!directed)
            adjList[v].push_back(u);
    }

    void removeEdge(int u, int v)
    {
        adjList[u].remove(v);        
    }

    void printGraph()
    {
        for (int i = 0; i < vertices; i++)
        {
            cout << i << " : ";
            for (auto v : adjList[i])
            {
                cout << v << " ";
            }
            cout << endl;
        }
    }
};

int main()
{
    freopen("input.in", "r", stdin);
    freopen("output.in", "w", stdout);
    graph g(4, 4, false);
    g.defineGraph();
    g.printGraph();
    g.removeEdge(1,2);
    g.printGraph();
    return 0;
}