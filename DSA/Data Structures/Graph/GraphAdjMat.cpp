#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class graph
{
    int vertices;
    int edges;
    bool directed;
    int **adjMat;
    int *prev;
    int *distance;

public:
    graph(int vertices, int edges, bool ifDirected)
    {
        this->vertices = vertices;
        this->edges = edges;

        /** have to locate memory for the container arrays first, then we can declare some size of array for each array */
        adjMat = new int *[this->vertices + 1];        
        for (int i = 1; i <= vertices; i++)
        {
            adjMat[i] = new int[vertices + 1];
        }
        
        directed = ifDirected;
        prev = new int[vertices + 1];
        distance = new int[vertices + 1];
    }

    void defineGraph()
    {
        for (int i = 1; i <= edges; i++)
        {
            int u, v;
            cin >> u >> v;
            addEdge(u, v);
        }
    }

    void addEdge(int u, int v)
    {
        adjMat[u][v] = true;
        if (!directed)
            adjMat[v][u] = true;
    }

    void removeEdge(int u, int v)
    {
        adjMat[u][v] = false;
        adjMat[v][u] = false;
    }

    bool isConnected(int u, int v)
    {
        return adjMat[u][v] or adjMat[v][u];
    }

    int outDegree(int u)
    {
        int outD = 0;
        for(int i=1; i<=vertices; i++)
        {
            outD += adjMat[u][i];
        }
        return outD;
    }

    int inDegree(int u)
    {
        int inD = 0;
        for(int i=1; i<=vertices; i++)
        {
            inD += adjMat[i][u];
        }
        return inD;
    }

    void printGraph()
    {
        for (int i = 1; i <= vertices; i++)
        {
            for (int j = 1; j <= vertices; j++)
                cout << adjMat[i][j] << " ";
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
    cout<<g.isConnected(1,3)<<endl;
    cout<<g.inDegree(2)<<endl;
    cout<<g.outDegree(2)<<endl;
    return 0;
}