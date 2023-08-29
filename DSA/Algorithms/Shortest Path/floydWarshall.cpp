#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

typedef pair<int, int> iPair;

enum COLORS
{
    white = 0, // not visited (not explored)
    grey = 1,  // visited but their neighbours are not visited (partially explored)
    black = 2  // visited along with all the neighbours (fully explored)
};

class triplet
{
public:
    int u, v, weight;
};

class graph
{
    vector<list<pair<int, int>>> adjList;
    int vertices;
    int edges;
    bool directed;
    COLORS *color;
    int *parent;
    int *distance;
    vector<vector<int>> dpMatrix;

public:
    graph(int vertices, int edges, bool ifDirected)
    {
        this->vertices = vertices;
        this->edges = edges;
        adjList.resize(vertices);
        directed = ifDirected;
        color = new COLORS[vertices];
        parent = new int[vertices];
        distance = new int[vertices];
        dpMatrix.resize(vertices, vector<int>(vertices));

        for (int i = 0; i < vertices; i++)
        {
            for (int j = 0; j < vertices; j++)
            {
                if (i == j)
                    dpMatrix[i][j] = 0;
                else
                    dpMatrix[i][j] = 1e9+5;
            }
        }
    }

    void defineGraph()
    {
        for (int i = 0; i < edges; i++)
        {
            int u, v, weight;
            cin >> u >> v >> weight;
            addEdge(u, v, weight);
        }
    }

    void addEdge(int u, int v, int weight)
    {
        adjList[u].push_back({v, weight});
        dpMatrix[u][v] = weight;
        if (!directed)
        {
            adjList[v].push_back({u, weight});
            dpMatrix[v][u] = weight;
        }
    }

    void printGraph()
    {
        for (int i = 0; i < vertices; i++)
        {
            cout << i << " : ";
            for (auto v : adjList[i])
            {
                cout << v.first << " (" << v.second << "), ";
            }
            cout << endl;
        }
    }

    void floydWarshall()
    {
        for (int k = 0; k < vertices; k++)
        {
            for (int i = 0; i < vertices; i++)
            {
                for (int j = 0; j < vertices; j++)
                {
                    if ((dpMatrix[i][j] > dpMatrix[i][k] + dpMatrix[k][j]) and (dpMatrix[i][k] != 1e9+5 and dpMatrix[k][j] != 1e9+5))
                    {
                        dpMatrix[i][j] = dpMatrix[i][k] + dpMatrix[k][j];
                    }
                }
            }
        }
        printShortestPath();
    }

private:
    void printShortestPath()
    {
        for (int i = 0; i < vertices; i++)
        {
            for (int j = 0; j < vertices; j++)
            {
                if (dpMatrix[i][j] == 1e9+5)
                    cout << "inf"
                         << " ";
                else
                    cout << dpMatrix[i][j] << " ";
            }
            cout << "\n";
        }
    }
};

int main()
{
    graph g(4, 4, true); // starts from 0
    g.defineGraph();
    g.printGraph();
    g.floydWarshall();
    return 0;
}