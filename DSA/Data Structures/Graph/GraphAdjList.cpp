#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class graph
{
    int vertices;
    int edges;
    bool directed;
    vector<list<int>> adjList;

    int *prev;
    int *distance;

public:
    graph(int vertices, int edges, bool ifDirected)
    {
        this->vertices = vertices;
        this->edges = edges;
        adjList.resize(vertices+1);
        directed = ifDirected;

        prev = new int[vertices + 1];
        distance = new int[vertices + 1];
    }

    void defineGraph()
    {
        for (int i = 0; i < edges; i++)
        {
            int u, v;
            cin >> u >> v;
            addEdge(u, v);
        }
    }

    void addEdge(int u, int v)
    {
        adjList[u].push_back(v);
        if (!directed)
            adjList[v].push_back(u);
    }

    void removeEdge(int u, int v)
    {
        adjList[u].remove(v);
    }

    bool isConnected(int u, int v)
    {
        //sort(adjList[u].begin(), adjList[u].end());
        adjList[u].sort();
        adjList[v].sort();
        return (binary_search(adjList[u].begin(), adjList[u].end(), v)) or (binary_search(adjList[v].begin(), adjList[v].end(), u));
    }

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
                if (v == u)
                    inD++; 
            }
        }
        
        return inD; 

        /** can be done with binary search as well */
        /** inD = 0;
        for (int i = 1; i <= vertices; i++)
        {
            sort(adjList[i].begin(), adjList[i].end());
            if(binary_search(adjList[i].begin(), adjList[i].end(), u)) 
                inD++;
        }
        return inD; */
    }

    void printGraph()
    {
        for (int i = 1; i <= vertices; i++)
        {
            cout << i << " : ";
            for (auto v : adjList[i])
            {
                cout << v << " ";
            }
            cout << endl;
        }
    }
};

int main()
{
    // freopen("input.in", "r", stdin);
    // freopen("output.in", "w", stdout);
    graph g(5, 6, true); //starts from 1
    g.defineGraph();
    g.printGraph();
    cout<<g.isConnected(3,1)<<endl;
    cout<<g.inDegree(2)<<endl;
    cout<<g.outDegree(2)<<endl;
    return 0;
}