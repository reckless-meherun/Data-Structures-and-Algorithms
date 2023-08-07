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
        // cout<<a<<" "<<b<<endl;
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
        // cout<<a<<" "<<b<<endl;
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

    // void removeEdge(int u, int v)
    // {
    //     adjList[u].remove({v, weight});
    // }

    // bool isConnected(int u, int v)
    // {
    //     // sort(adjList[u].begin(), adjList[u].end());
    //     adjList[u].sort();
    //     adjList[v].sort();
    //     return (binary_search(adjList[u].begin(), adjList[u].end(), v)) or (binary_search(adjList[v].begin(), adjList[v].end(), u));
    // }

    int outDegree(int u)
    {
        return adjList[u].size();
    }

    int inDegree(int u)
    {
        if (!directed)
            return outDegree(u);

        int inD = 0;
        for (int i = 0; i < vertices; i++)
        {
            for (auto v : adjList[i]) /** inDegree : how many times u is in the lists of each vertex list */
            {
                if (v.first == u)
                    inD++;
            }
        }

        return inD;

        /** can be done with binary search as well */
        /** inD = 0;
        for (int i = 0; i < vertices; i++)
        {
            sort(adjList[i].begin(), adjList[i].end());
            if(binary_search(adjList[i].begin(), adjList[i].end(), u))
                inD++;
        }
        return inD; */
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
        return a.weight <= b.weight;
    }

public:
    void mstKruskals()
    {
        vector<triplet> minEdge;
        int cost = 0;
        dsu minSpanTree(vertices);
        sort(edgeList.begin(), edgeList.end(), cmp);
        for (auto e : edgeList)
        {
            if (!minSpanTree.hasCycle(e.u, e.v))
            {
                minSpanTree.Union(e.u, e.v);
                cost += e.weight;
                minEdge.push_back({e.u, e.v, e.weight});
            }
        }
        cout << "Minimum cost : " << cost << endl;
        printMST(minEdge);
    }

    void printMST(vector<triplet> minEdge)
    {
        for (auto a : minEdge)
        {
            cout << a.u << " - " << a.v << " : " << a.weight << "\n";
        }
    }

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
    graph g(4, 5, false); // starts from 1
    g.defineGraph();
    g.printGraph();
    cout<<"\n";
    g.mstKruskals();
    //g.printEdgelist();
    return 0;
}