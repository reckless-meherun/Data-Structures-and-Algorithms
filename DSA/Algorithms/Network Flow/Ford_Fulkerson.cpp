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
    vector<vector<int>> dpMatrix;
    vector<vector<int>> predecMatrix;
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
        predecMatrix.resize(vertices, vector<int>(vertices, -1));
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
        predecMatrix[u][v] = u;
        if (!directed)
        {
            adjList[v].push_back({u, w});
            dpMatrix[v][u] = w;
            predecMatrix[v][u] = v;
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
            predecMatrix[source][i] = -1;
        }
        distance[source] = 0;
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
    
    bool isPath = false;

    bool DFS(int source, int destination)
    {
        initialize(source);
        DFS_Visit(source, destination);
        return isPath;
    }

private:
    void DFS_Visit(int u, int t)
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
                if (v.v == t)
                    isPath = true;
                DFS_Visit(v.v, t);
            }
        }
        endTime[u] = time;
        // cout << "leaving vertex " << u << " at " << endTime[u] << endl;
        time++;
        color[u] = black;
    }

    int ford_fulkerson(graph res, int s, int t)
    {
        int max_flow = 0;
        while (res.DFS(s, t))
        {
            int path_flow = MAX_VALUE;
            for (int v = t; v != s; v = parent[v])
            {
                path_flow = min(path_flow, adjList[parent[v]][v].v); // somossa ase
            }
            for (int v = t; v != s; v = parent[v]) // somossa ase
            {
                int u = parent[v];
                adjList[u][v].v -= path_flow;
                adjList[v][u].v += path_flow;
            }
            max_flow += path_flow;
        }
        return max_flow;
    }
};

int main()
{
    graph g(6, 10, true, true);

    return 0;
}