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
    vector<COLORS> color;
    vector<int> parent;
    vector<int> distance;
    vector<int> topoOrder;
    bool directed;
    bool weighted;
    bool hasCycle = false;
    vector<int> startTime;
    vector<int> endTime;
    vector<vector<int>> scc;
    int totalSCC = 0;
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
        topoOrder.reserve(vertices);
        startTime.resize(vertices);
        endTime.resize(vertices);
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
        if (!directed)
        {
            adjList[v].push_back({u, w});
        }
        edgeList.push_back({u, v, w});
    }

    // void removeEdge(int u, int v, int w)
    // {
    //     adjList[u].erase(adjList[u].find({v, w}));
    // }

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

private:
    void initialize(int source)
    {
        time = 1;
        for (int i = 0; i < vertices; i++)
        {
            color[i] = white;
            parent[i] = -1;
            distance[i] = MAX_VALUE;
            startTime[i] = 0;
            endTime[i] = 0;
        }
        distance[source] = 0;
    }

    void DFS(int source)
    {
        initialize(source);
        DFS_Visit(source);
    }

    void DFS()
    {
        initialize(0);
        for (int i = 0; i < vertices; i++)
        {
            if (color[i] == white)
            {
                DFS_Visit(i);
            }
        }
    }

    void DFS(vector<int> orderedNodes)
    {
        initialize(orderedNodes[0]);
        for (auto u : orderedNodes)
        {
            if (color[u] == white)
            {
                DFS_Visit(u);
                totalSCC++;
                cout << "\n";
            }
        }
    }

    void DFS_Visit(int u)
    {
        color[u] = grey;
        startTime[u] = time;
        time++;
        cout << u << " entering at time " << startTime[u] << endl;
        for (auto v : adjList[u])
        {
            if (color[v.v] == grey)
                hasCycle = true;
            if (color[v.v] == white)
            {
                color[v.v] = grey;
                parent[v.v] = u;
                distance[v.v] = distance[u] + 1;
                DFS_Visit(v.v);
            }
        }
        color[u] = black;
        endTime[u] = time;
        time++;
        cout << u << " leaving at time " << endTime[u] << endl;
        topoOrder.push_back(u);
    }

public:
    vector<int> topologicalSort()
    {
        DFS();
        reverse(topoOrder.begin(), topoOrder.end());
        if (hasCycle)
            cout << "The sort is not topological\n";

        for (auto a : topoOrder)
            cout << a << " ";
        cout << "\n";
        return topoOrder;
    }

    void transpose()
    {
        vector<vector<duplet>> adjList2(vertices);
        if (!directed)
            return;

        for (int i = 0; i < vertices; i++)
        {
            for (auto v : adjList[i])
            {
                adjList2[v.v].push_back({i, v.weight});
            }
        }
        adjList = adjList2;
    }

    void findSCC()
    {
        auto orderedNodes = topologicalSort();
        // printGraph();
        // cout<<endl;
        transpose();
        // printGraph();
        cout << "SCC:\n";
        DFS(orderedNodes);
        cout << "total SCC " << totalSCC << endl;
        transpose();
    }

    bool isConnected()
    {
        if (!directed)
        {
            DFS(0);
            for (int i = 0; i < vertices; i++)
                if (color[i] == white and adjList[i].size() > 0)
                    return false;
            return true;
        }
        else
        {
            vector<bool> visited1(vertices);
            DFS(0);

            for(int i=0; i<vertices; i++)
            {
                if(color[i]!=white)
                    visited1[i]=true;
            }

            transpose();

            vector<bool>visited2(vertices);
            DFS(0);

            for(int i=0; i<vertices; i++)
            {
                if(color[i]!=white)
                    visited2[i]=true;
            }

            transpose(); //back to the original

            for(int i=0; i<vertices; i++)
            {
                if(!visited1[i] and !visited2[i])
                    return false;
            }
            return true;
        }
    }
};

int main()
{
    int m, n;
    cin >> m >> n;
    graph g(m, n, true, false);
    // g.printGraph();
    // g.topologicalSort();
    // g.findSCC();
    g.printGraph();
    return 0;
}