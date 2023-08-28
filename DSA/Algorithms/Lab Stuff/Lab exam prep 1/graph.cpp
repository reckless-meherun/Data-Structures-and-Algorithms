#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define MAX_VALUE 1e9 + 7;

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
        adjList.resize(vertices);
        edgeList.resize(edges);
        parent.resize(vertices);
        distance.resize(vertices);
        color.resize(vertices);
        startTime.resize(vertices);
        endTime.resize(vertices);
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
            for (int i = 0; i < edges; i++)
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

    void BFS(int source)
    {
        initialize(source);
        color[source] = grey;
        queue<int> greyVertices;

        greyVertices.push(source);

        while (!greyVertices.empty())
        {
            int u = greyVertices.front();
            greyVertices.pop();

            for (auto v : adjList[u])
            {
                if (color[v.v] == white)
                {
                    parent[v.v] = u;
                    distance[v.v] += distance[u] + 1;
                    color[v.v] = grey;
                    greyVertices.push(v.v);
                }
            }
            color[u] = black;
        }
    }

    void printPath(int source, int destination)
    {
        if (source == destination)
        {
            cout << source << " ";
        }
        else if (parent[destination] == -1)
        {
            cout << "no path\n";
        }
        else
        {
            printPath(source, parent[destination]);
            cout << destination << " ";
        }
    }
    void DFS(int source)
    {
        initialize(source);
        DFS_Visit(source);
    }

private:
    void DFS_Visit(int u)
    {
        color[u] = grey;
        startTime[u] = time;
        // cout << "entering vertex " << u << " at " << startTime[u] << endl;
        time++;
        for (auto v : adjList[u])
        {
            if (color[v.v] == white)
            {
                color[v.v] = grey;
                parent[v.v] = u;
                distance[v.v] = distance[u] + 1;
                DFS_Visit(v.v);
            }
        }
        endTime[u] = time;
        // cout << "leaving vertex " << u << " at " << endTime[u] << endl;
        time++;
        color[u] = black;
    }

public:
    void printStartingTimes()
    {
        for (int i = 0; i < vertices; i++)
            cout << i << " : " << startTime[i] << "\n";
        cout << "\n";
    }

    void printFinishingTimes()
    {
        for (int i = 0; i < vertices; i++)
            cout << i << " : " << endTime[i] << "\n";
        cout << "\n";
    }

private:
    static bool cmp(duplet &a, duplet &b)
    {
        if (a.weight == b.weight)
            return a.v > b.v;
        return a.weight > b.weight;
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

            for (auto v : adjList[u])
            {
                if (color[v.v] == white)
                {
                    if (distance[v.v] > distance[u] + v.weight) // relax
                    {
                        parent[v.v] = u;
                        distance[v.v] = distance[u] + v.weight;
                        minHeap.push({v.v, distance[v.v]});
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

    bool relax(int u, int v, int w)
    {
        if (distance[v] > distance[u] + w)
        {
            distance[v] = distance[u] + w;
            parent[v] = u;
            return true;
        }
        return false;
    }

    bool bellmanFord(int source, int destination)
    {
        initialize(source);
        for (int i = 0; i < vertices - 1; i++)
        {
            for (auto e : edgeList)
            {
                relax(e.u, e.v, e.weight);
            }
        }
        for (int i = 0; i < vertices - 1; i++)
        {
            for (auto e : edgeList)
            {
                if (relax(e.u, e.v, e.weight))
                {
                    cout << "Negative cycle exists\n";
                    return false;
                }
            }
        }

        if (distance[destination] == 1e9 + 7)
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
    graph g(m, n, false, true); // starts from 0
    int q;
    cin >> q;
    while (q--)
    {
        int x, y;
        cin >> x >> y;
        g.dijkstra(x);
        g.printPath(x, y);
        cout << "\n";
    }
    return 0;
}