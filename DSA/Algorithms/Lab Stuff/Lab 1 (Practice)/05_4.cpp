#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

enum COLORS
{
    white = 0, 
    grey = 1,  
    black = 2  
};

class graph
{
    int vertices;
    int edges;
    bool directed;
    vector<list<int>> adjList;
    int *parent;
    int *distance;
    COLORS *color;
    bool hasCycle;

public:
    graph(int vertices, int edges, bool ifDirected)
    {
        this->vertices = vertices;
        this->edges = edges;
        adjList.resize(vertices);
        directed = ifDirected;
        parent = new int[vertices];
        distance = new int[vertices];
        color = new COLORS[vertices];
        hasCycle = false;
    }

    void defineGraph()
    {
        for (int i = 0; i < edges; i++)
        {
            int u, v;
            cin >> u >> v;
            addEdge(u, v);
            //cout<<u<<" "<<v<<endl;
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

    void printGraph()
    {
        for (int i = 0; i < vertices; i++)
        {
            cout << i << " : ";
            for (auto v : adjList[i])
            {
                cout << v << " ";
            }
            cout << endl;
        }
    }

    void initialize()
    {
        // initialize loop
        for (int i = 0; i < vertices; i++)
        {
            color[i] = white;
            for (auto v : adjList[i])
            {
                color[v] = white;
                parent[v] = INT_MIN;
                distance[v] = INT_MAX;
            }
        }
    }

    void DFS()
    {
        initialize();

        for (int i = 0; i < vertices; i++) 
            if (color[i] == white)
                DFS_Visit(i);
    }

private:
    void DFS_Visit(int u)
    {
        color[u] = grey;
        int children = 0;
        for (auto v : adjList[u])
        {
            if (color[v] == grey and v!=parent[u])
                hasCycle = true;
            if (color[v] == white)
            {
                color[v] = grey;
                distance[v] = distance[u] + 1;
                parent[v] = u;
                children++; 

                DFS_Visit(v);
            }
        }
        color[u] = black;
    }

public:
    bool hasACycle()
    {
        return hasCycle;
    }
};

int main()
{
    freopen("input.in", "r", stdin);
    freopen("output.in", "w", stdout);
    int m, n;
    cin>>m>>n;
    graph g(m, n, false); //starts from 0
    g.defineGraph();    
    g.DFS();
    //g.printGraph();
   if(g.hasACycle())
    cout<<"Yes\n";
    else
    cout<<"No\n";

    
    return 0;
}