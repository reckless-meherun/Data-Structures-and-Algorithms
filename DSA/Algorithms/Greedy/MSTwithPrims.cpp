#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class triplet
{
public:
    int u, v, weight;
};

class graph
{
    int vertices;
    int edges;
    bool directed;
    vector<list<pair<int, int>>> adjList;
    int *parent;
    int *distance;
    bool *mst;

public:
    graph(int vertices, int edges, bool ifDirected)
    {
        this->vertices = vertices;
        this->edges = edges;
        adjList.resize(vertices);
        directed = ifDirected;
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
    int findMinVertex()
    {
        int minVertex;
        int minDistance = INT_MAX;
        for (int i = 0; i < vertices; i++)
        {
            if (mst[i] == false and distance[i] < minDistance)
            {
                minVertex = i;
                minDistance = distance[i];
                // cout << "minimum key : " << minDistance << endl;
            }
        }
        return minVertex;
    }

public:
    void mstPrims()
    {
        int cost = 0;
        mst = new bool[vertices];
        int minEdgeCost[vertices][vertices];
        vector<triplet> minSpanTree;

        for (int i = 0; i < vertices; i++)
        {
            distance[i] = INT_MAX;
            mst[i] = false;
            parent[i] = -1;
        }

        parent[0] = -1;
        distance[0] = -1;

        for (int i = 0; i < vertices; i++)
        {
            int u = findMinVertex();
            mst[u] = true;

            for (auto v : adjList[u]) // relax
            {
                if (mst[v.first] == false and v.second < distance[v.first])
                {
                    distance[v.first] = v.second; // v.first = vertex, v.second = 'u - v.first' edge weight
                    parent[v.first] = u;
                    minEdgeCost[v.first][u] = v.second;
                    minEdgeCost[u][v.first] = v.second; // assigning in both so that no index error occurs in either way
                }
            }

            // cost calculation and assinging to minimum spanning tree for printing
            if (parent[i] != -1)
            {
                cost += minEdgeCost[u][parent[u]];
                minSpanTree.push_back({parent[u], u, minEdgeCost[parent[u]][u]});
            }
        }
        cout << "Minimum cost : " << cost << "\n";
        printMST(minSpanTree);
    }

private:
    void printMST(vector<triplet> minSpanTree)
    {
        for (auto a : minSpanTree)
        {
            cout << a.u << " - " << a.v << " : " << a.weight << "\n";
        }
    }
};

int main()
{
    graph g(4, 5, false); // starts from 0
    g.defineGraph();
    g.printGraph();
    cout<<"\n";
    g.mstPrims();
    return 0;
}