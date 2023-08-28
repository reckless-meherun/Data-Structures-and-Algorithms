#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

typedef pair<int, int> iPair;
int sum = 0;
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
    vector<vector<int>> predecMatrix;

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
        predecMatrix.resize(vertices, vector<int>(vertices));

        for (int i = 0; i < vertices; i++)
        {
            for (int j = 0; j < vertices; j++)
            {
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
        adjList[u].push_back({v, weight});
        predecMatrix[u][v] = weight;
        if (!directed)
        {
            adjList[v].push_back({u, weight});
            predecMatrix[v][u] = weight;
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
                    if ((predecMatrix[i][j] > predecMatrix[i][k] + predecMatrix[k][j]) and (predecMatrix[i][k] != INT_MAX and predecMatrix[k][j] != INT_MAX))
                    {
                        predecMatrix[i][j] = predecMatrix[i][k] + predecMatrix[k][j];
                    }
                }
            }
        }
        //printShortestPath();
    }

    void countSum(int source, int dest)
    {
        //if (predecMatrix[source][dest] != INT_MAX)
            sum += predecMatrix[source][dest];
    }

private:
    void printShortestPath()
    {
        for (int i = 0; i < vertices; i++)
        {
            for (int j = 0; j < vertices; j++)
            {
                if (predecMatrix[i][j] == INT_MAX)
                    cout << "inf"
                         << " ";
                else
                    cout << predecMatrix[i][j] << " ";
            }
            cout << "\n";
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

    int r;
    cin >> r;
    int i = 0;
    int apart[r];
    int test = r;
    while (r--)
    {
        cin >> apart[i];
        i++;
    }

    for(int j=0; j<test; j++)
    {
        if ((j + 1) < test)
            g.countSum(apart[j], apart[j + 1]);
    }
    cout << sum << endl;
    return 0;
}