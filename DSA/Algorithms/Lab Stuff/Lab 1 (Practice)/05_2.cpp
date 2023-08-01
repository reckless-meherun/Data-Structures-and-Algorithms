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

    void BFS(int source)
    {
        initialize();

        queue<int> grey_ver; 

        color[source] = grey;
        distance[source] = 0;
        grey_ver.push(source);

        while (!grey_ver.empty())
        {
            int u = grey_ver.front();
            grey_ver.pop();
            for (auto v : adjList[u])
            {
                if (color[v] == white)
                {
                    color[v] = grey;
                    distance[v] = distance[u] + 1;
                    parent[v] = u;
                    grey_ver.push(v);
                }
            }
            color[u] = black; 
        }
    }

    void printPathLengths(int source)
    {
        BFS(source);
        for(int i=0; i<vertices; i++)
        {
            if(color[i] !=white)
                cout<<i<<" : "<<distance[i]<<"\n";
            else
                cout<<i<<" : Not Reachable\n";
        }
    }
};

int main()
{
    freopen("input.in", "r", stdin);
    freopen("output.in", "w", stdout);
    int m, n;
    cin>>m>>n;
    graph g(m, n, true); //starts from 1
    g.defineGraph();    
    g.printPathLengths(0);
       
    return 0;
}