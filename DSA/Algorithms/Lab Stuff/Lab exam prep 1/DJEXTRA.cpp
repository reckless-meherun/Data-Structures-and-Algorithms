#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define MAX_VALUE 1e8 + 5;

enum COLORS
{
    white = 0,
    grey = 1,
    black = 2
};

class duplet
{
public:
    int v, weight;
};

class triplet
{
public:
    int u, v, weight;
};

class graph
{
    int vertices;
    int edges;
    vector<vector<duplet>> adjList;
    vector<triplet> edgeList;
    vector<COLORS> color;
    vector<int> parent;
    vector<int> distance;
    vector<int> startTime;
    vector<int> endTime;
    bool directed;
    bool weighted;
    int time = 1;

public:
    graph(int vertices, int edges, bool directed, bool weighted)
    {
        this->vertices = vertices;
        this->edges = edges;
        this->directed = directed;
        this->weighted = weighted;
        adjList.reserve(vertices);
        edgeList.reserve(edges);
        parent.reserve(vertices);
        distance.reserve(vertices);
        color.reserve(vertices);
        startTime.reserve(vertices);
        endTime.reserve(vertices);
        defineGraph(weighted);
    }

private:
    void defineGraph(bool weighted)
    {
        int u, v, weight;
        if (!weighted)
        {
            for (int i = 0; i < edges; i++)
            {
                cin >> u >> v;
                addEdge(u, v);
            }
        }
        else
        {
            for (int i = 0; i < vertices; i++)
            {
                cin >> u >> v >> weight;
                addEdge(u, v, weight);
            }
        }
    }

    void addEdge(int u, int v)
    {
        adjList[u].push_back({v, 1});
        if (!directed)
            adjList[v].push_back({u, 1});
        edgeList.push_back({u, v, 1});
    }

    void addEdge(int u, int v, int w)
    {
        adjList[u].push_back({v, w});
        if (!directed)
            adjList[v].push_back({u, w});
        edgeList.push_back({u, v, w});
    }

public:
    void printGraph()
    {
        if (!weighted)
        {
            for (int i = 0; i < vertices; i++)
            {
                cout << i << " : ";
                for (auto u : adjList[i])
                {
                    cout << u.v << " ";
                }
                cout << "\n";
            }
        }
        else
        {
            for (int i = 0; i < vertices; i++)
            {
                cout << i << " : ";
                for (auto u : adjList[i])
                {
                    cout << u.v << "(" << u.weight << ") ";
                }
                cout << "\n";
            }
        }
    }

    void initialize(int source)
    {
        time = 1;
        for (int i = 0; i < vertices; i++)
        {
            color[i] = white;
            distance[i] = MAX_VALUE;
            parent[i] = -1;
        }
        distance[source] = 0;
    }

private:
    static bool cmp(duplet &a, duplet &b)
    {
        return a.weight <= b.weight;
    }

public:
    void dijkstra(int source)
    {
        initialize(source);
        priority_queue<duplet, vector<duplet>, decltype(&cmp)> minHeap;
        minHeap.push({source, 0});

        while (!minHeap.empty())
        {
            duplet node = minHeap.top();
            minHeap.pop();
            int u = node.v;

            if (color[u] != white)
                continue;
            color[u] = grey;

            cout << u << endl;
            for (auto v : adjList[u])
            {
                if (color[v.v] == white)
                {
                    if (distance[v.v] > distance[u] + v.weight) // relax
                    {
                        parent[v.v] = u;
                        distance[v.v] = distance[u] + v.weight;
                        minHeap.push({v.v, v.weight});
                    }
                }
            }
        }

        // for (int i = 0; i < vertices; i++)
        // {
        //     if (source != i and distance[i] != 0)
        //         cout << i << " : " << distance[i] << "\n";
        //     else if (source != i and distance[i] == 0)
        //         cout << i << " : " << -1 << "\n";
        // }
    }
};

int main()
{
    int m, n;
    cin >> m >> n;
    graph g(m, n, false, true);
    // g.printGraph();
    g.dijkstra(0);

    return 0;
}
