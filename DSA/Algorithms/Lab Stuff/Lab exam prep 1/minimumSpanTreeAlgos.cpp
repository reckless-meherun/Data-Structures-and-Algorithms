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
    vector<bool> mst;
    bool directed;
    bool weighted;

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
        mst.resize(vertices, false);
        
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

    void intialize(int source)
    {
        for (int i = 0; i < vertices; i++)
        {
            color[i] = white;
            parent[i] = -1;
            distance[i] = MAX_VALUE;
            mst[i] = false;
        }
        distance[source] = 0;
    }

    void mstPrims(int source)
    {
        intialize(source);
        vector<triplet> minSpanTree;
        priority_queue<iPair, vector<iPair>, greater<iPair>> pq;
        vector<vector<int>> edgeCost(vertices, vector<int>(vertices));
        int minCost = 0;
       
        pq.push({0, source});

        while (!pq.empty())
        {
            
            int u = pq.top().second;
            pq.pop();

            if (mst[u])
                continue;

            for (auto v : adjList[u])
            {
                if (mst[v.v] == false and distance[v.v] > v.weight)
                {
                    distance[v.v] = v.weight;
                    parent[v.v] = u;
                    edgeCost[u][v.v] = v.weight;
                    edgeCost[v.v][u] = v.weight;
                    pq.push({distance[v.v], v.v});
                }
            }
            if (parent[u] != -1)
            {
                minCost += edgeCost[parent[u]][u];
                minSpanTree.push_back({parent[u], u, edgeCost[parent[u]][u]});
            }
            mst[u] = true;
        }

        printMST(minSpanTree);
        cout << "Minimum cost : " << minCost << "\n";
    }

    void printMST(vector<triplet> minSpanTree)
    {
        for (auto tree : minSpanTree)
        {
            cout << tree.u << " - " << tree.v << " : " << tree.weight << "\n";
        }
    }
};

int main()
{
    int m, n;
    cin >> m >> n;
    graph g(m, n, true, true);
    g.mstPrims(0);
    return 0;
}