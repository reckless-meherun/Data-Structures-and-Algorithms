#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

enum COLORS
{
    white = 0, // not visited (not explored)
    grey = 1,  // visited but their neighbours are not visited (partially explored)
    black = 2  // visited along with all the neighbours (fully explored)
};

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
        adjList[u].push_back(v);
        if (!directed)
            adjList[v].push_back(u);
    }

    void removeEdge(int u, int v)
    {
        adjList[u].remove(v);
    }

    void BFS(int source)
    {
        COLORS color[vertices + 1];

        // initialize loop
        for (int i = 0; i < vertices; i++)
        {
            for (auto v : adjList[i])
            {
                color[v] = white;
                prev[v] = INT_MIN;
                distance[v] = INT_MAX;
            }
        }

        queue<int> grey_ver; // vertices that are grey/visited

        color[source] = grey;
        distance[source] = 0;
        grey_ver.push(source);

        while (!grey_ver.empty())
        {
            int u = grey_ver.front();
            grey_ver.pop();
            for (auto v : adjList[u])
            {
                if (color[v] == white)
                {
                    color[v] = grey;
                    distance[v] = distance[u] + 1;
                    prev[v] = u;
                    grey_ver.push(v);
                }
            }
            color[u] = black; // cause it has been fully explored
        }
    }

    void printShortestPath(int source, int destination)
    {
        if (source == destination)
        {
            cout << source << " ";
        }
        else if (prev[destination] == INT_MIN)
        {
            cout << "No path" << endl;
        }
        else
        {
            printShortestPath(source, prev[destination]);
            cout << destination << " ";
        }
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
    // freopen("input.in", "r", stdin);
    // freopen("output.in", "w", stdout);
    graph g(4, 4, false);
    g.defineGraph();
    g.printGraph();
    g.BFS(2);
    g.printShortestPath(2, 0);
    return 0;
}