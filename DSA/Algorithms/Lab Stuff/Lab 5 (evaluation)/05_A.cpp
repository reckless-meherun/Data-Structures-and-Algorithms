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
    //vector<list<pair<int, int>>> adjList;
    vector<vector<int>> adjList;
    int vertices;
    int edges;
    bool directed;
    COLORS *color;
    int *parent;
    int *distance;
    vector<vector<int>> predecMatrix;
    vector<triplet> edgeList;

public:
    graph(int vertices, int edges, bool ifDirected)
    {
        this->vertices = vertices;
        this->edges = edges;
        //adjList.resize(vertices);
        directed = ifDirected;
        color = new COLORS[vertices];
        parent = new int[vertices];
        distance = new int[vertices];
        predecMatrix.resize(vertices, vector<int>(vertices));
        adjList.resize(vertices, vector<int>(vertices));

        for (int i = 0; i < vertices; i++)
        {
            for (int j = 0; j < vertices; j++)
            {
                adjList[i][j] = INT_MAX;
                if (i == j)
                    predecMatrix[i][j] = 0;
                else
                    predecMatrix[i][j] = INT_MAX;
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
        //adjList[u].push_back({v, weight});
        adjList[u][v] = min(adjList[u][v], weight);
        predecMatrix[u][v] = weight;
        if (!directed)
        {
            adjList[v][u] = min(adjList[v][u], weight);
            predecMatrix[v][u] = weight;
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
                    if ((predecMatrix[i][j] > predecMatrix[i][k] + predecMatrix[k][j]) and (predecMatrix[i][k] != INT_MAX and predecMatrix[k][j] != INT_MAX))
                    {
                        predecMatrix[i][j] = predecMatrix[i][k] + predecMatrix[k][j];
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
            for (int j = i + 1; j < vertices; j++)
            {
                cout << i << " to " << j << ": ";
                if (predecMatrix[i][j] == INT_MAX)
                    cout << "infinity"
                         << "\n";
                else
                    cout << predecMatrix[i][j] << "\n";
            }
        }
    }
};

int main()
{
    int m, n;
    cin >> m >> n;
    graph g(m, n, false); // starts from 0
    g.defineGraph();
    g.floydWarshall();
    return 0;
}