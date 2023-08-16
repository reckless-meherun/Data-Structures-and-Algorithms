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
    vector<triplet> edgeList;
    vector<vector<int>> shortestPath;

public:
    graph(int vertices, int edges, bool ifDirected)
    {
        this->vertices = vertices;
        this->edges = edges;
        adjList.resize(vertices);
        shortestPath.resize(vertices);
        directed = ifDirected;
        color = new COLORS[vertices];
        parent = new int[vertices];
        distance = new int[vertices];
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
        if (!directed)
            adjList[v].push_back({u, weight});
        edgeList.push_back({u, v, weight});
        // cout<<u<<" "<<v<<" "<<weight<<"\n";
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

private:
    void initialize(int source)
    {
        for (int i = 0; i < vertices; i++)
        {
            distance[i] = 1e9+7;
            parent[i] = INT_MIN;
        }
        distance[source] = 0;
    }

    bool relax(int u, int v, int weight)
    {
        if (distance[v] > distance[u] + weight)
        {
            distance[v] = distance[u] + weight;
            parent[v] = u;
            
            return true;
        }
        return false;
    }

public:
    bool bellman_ford(int source, int destination)
    {
        initialize(source);
        for (int i = 0; i < vertices - 1; i++)
        {

            for (auto e : edgeList)
            {
                relax(e.u, e.v, e.weight);
    
            }
        }
        
        // checking negative cycles
        for (auto e : edgeList)
        {
            if (relax(e.u, e.v, e.weight))
            {
                cout << "Negative cycle exists; Bellman_Ford is not possible\n";
                return false;
            }
        }

        // printing the distances from source
        if (distance[destination] == 1e9+7)
            cout << "Impossible\n";
        else
            cout << distance[destination] << "\n";
        return true;
    }
};

int main()
{
    int m, n;
    cin >> m >> n;
    graph g(m, n, true); // starts from 0
    g.defineGraph();
    //g.printGraph();
    int q;
    cin >> q;
    while (q--)
    {
        int x, y;
        cin >> x >> y;
        g.bellman_ford(x, y);
    }
    return 0;
}