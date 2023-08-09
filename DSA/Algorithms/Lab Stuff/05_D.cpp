#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class triplet
{
public:
    int u, v, weight;
};

class dsu
{
    int *parent, *rank, size;

public:
    dsu(int size)
    {
        this->size = size;
        parent = new int[size];
        rank = new int[size];
        memset(parent, -1, sizeof(parent));
        memset(rank, -1, sizeof(rank));
        makeSet();
    }
    void makeSet()
    {
        for (int v = 0; v < size; v++)
        {
            parent[v] = v;
            rank[v] = 1;
        }
    }
    void make(int a)
    {
        parent[a] = a;
        rank[a] = 1;
    }
    int findRoot(int v)
    {
        if (v == parent[v])
            return v;
        return parent[v] = findRoot(parent[v]); /** the return value is the same for both optimized and unoptimized version; but here we are just resetting the parent of every node to root on the way back home recursion so that it takes much less time for the next findRoot that will be called */
    }
    void Union(int a, int b)
    {
        a = findRoot(a);
        b = findRoot(b);
        if (a == b)
            return;
        if (rank[a] < rank[b])
        {
            parent[a] = b;
        }
        else if (rank[a] > rank[b])
        {
            parent[b] = a;
        }
        else
        {
            parent[b] = a;
            rank[a]++;
        }
    }

    bool hasCycle(int u, int v)
    {
        //Union(u, v);
        int rootU = findRoot(u);
        int rootV = findRoot(v);

        if (rootU == rootV)
            return true;
        return false;
    }
};

class graph
{
    int vertices;
    int edges;
    bool directed;
    vector<list<pair<int, int>>> adjList;
    vector<triplet> edgeList;

    int *parent;
    int *distance;
    bool *mst;
    int *key;

public:
    graph(int vertices, int edges, bool ifDirected)
    {
        this->vertices = vertices;
        this->edges = edges;
        adjList.resize(vertices + 1);
        directed = ifDirected;
        //edgeList.resize(vertices + 1);
        parent = new int[vertices + 1];
        distance = new int[vertices + 1];
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
        edgeList.push_back({u, v, weight}); // triplet
        adjList[u].push_back({v, weight});
        if (!directed)
            adjList[v].push_back({u, weight});
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
    static bool cmp(triplet &a, triplet &b) // this is inside graph class that's why u gotta use static here
    {
        return a.weight >= b.weight;
    }

public:
    void mstKruskals()
    {
        vector<triplet> maxEdge;
        int cost = 0;
        dsu maxSpanTree(vertices);
        sort(edgeList.begin(), edgeList.end(), cmp);
        for (auto e : edgeList)
        {
            if (!maxSpanTree.hasCycle(e.u, e.v))
            {
                maxSpanTree.Union(e.u, e.v);
                cost += e.weight;
                maxEdge.push_back({e.u, e.v, e.weight});
            }
        }
        cout<< cost << endl;
        //printMST(maxEdge);
    }

private:
    void printMST(vector<triplet> maxEdge)
    {
        for (auto a : maxEdge)
        {
            cout << a.u << " - " << a.v << " : " << a.weight << "\n";
        }
    }

public:
    void printEdgelist()
    {
        for(auto a: edgeList)
        {
            cout<<a.u<<" - "<<a.v<<" : "<<a.weight<<"\n";
        }
    }
};

int main()
{
    int m,n;
    cin>>m>>n;
    graph g(m, n, false); // starts from 0
    g.defineGraph();
    g.mstKruskals();
    return 0;
}