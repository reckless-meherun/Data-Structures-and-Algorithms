#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

typedef pair<int, int> iPair;
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
    vector<vector<int>> dpMatrix;
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
        dpMatrix.resize(vertices, vector<int>(vertices, 1e9 + 7));
        parent.resize(vertices);
        distance.resize(vertices);
        color.resize(vertices);
        startTime.resize(vertices);
        endTime.resize(vertices);

        // initialize diagonals
        for (int i = 0; i < vertices; i++)
            for (int j = 0; j < vertices; j++)
                if (i == j)
                    dpMatrix[i][j] = 0;

        defineGraph(weighted);
    }

private:
    void defineGraph(bool weighted)
    {
        int u, v, weight = 1;
        for (int i = 0; i < edges; i++)
        {
            if (!weighted)
            {
                cin >> u >> v;
            }
            else
            {
                cin >> u >> v >> weight;
            }
            addEdge(u, v, weight);
        }
    }

    void addEdge(int u, int v, int w)
    {
        adjList[u].push_back({v, w});
        dpMatrix[u][v] = w;
        if (!directed)
        {
            adjList[v].push_back({u, w});
            dpMatrix[v][u] = w;
        }
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

    // private:
    //     static bool cmp(const duplet &a, const duplet &b)
    //     {
    //         if (a.weight == b.weight)
    //             return a.v < b.v;
    //         return a.weight < b.weight;
    //     }

public:
    void dijkstra(int source)
    {
        initialize(source);
        priority_queue<iPair, vector<iPair>, greater<iPair>> minHeap;
        minHeap.push({0, source});

        while (!minHeap.empty())
        {
            int u = minHeap.top().second;
            minHeap.pop();

            if (color[u] != white)
                continue;
            color[u] = black;

            for (auto v : adjList[u])
            {
                if (distance[v.v] > distance[u] + v.weight) // relax
                {
                    parent[v.v] = u;
                    distance[v.v] = distance[u] + v.weight;
                    minHeap.push({distance[v.v], v.v});
                }
            }
        }

        for (int i = 0; i < vertices; i++)
        {
            if (distance[i] != 1e9 + 7)
                cout << i << " : " << distance[i] << "\n";
            else
                cout << i << " : " << -1 << "\n";
        }
    }

private:
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

public:
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

    void floydWarshall()
    {

        for (int k = 0; k < vertices; k++)
        {
            for (int i = 0; i < vertices; i++)
            {
                for (int j = 0; j < vertices; j++)
                {
                    if ((dpMatrix[i][k] != 1e9 + 7 and dpMatrix[k][j] != 1e9 + 7) and (dpMatrix[i][j] > dpMatrix[i][k] + dpMatrix[k][j]))
                        dpMatrix[i][j] = min(dpMatrix[i][j], dpMatrix[i][k] + dpMatrix[k][j]);
                }
            }
        }

        for (int i = 0; i < vertices; i++)
        {
            for (int j = 0; j < vertices; j++)
            {
                if (dpMatrix[i][j] != 1e9 + 7)
                    cout << dpMatrix[i][j] << " ";
                else
                    cout << "inf ";
            }
            cout << "\n";
        }
    }
};

int main()
{
    int m, n;
    cin >> m >> n;
    graph g(m, n, true, true); // starts from 0
                               // g.printGraph();
    g.floydWarshall();
    return 0;
}
