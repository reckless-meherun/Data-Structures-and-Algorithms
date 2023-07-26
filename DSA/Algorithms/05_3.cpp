#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

enum COLORS
{
    white = 0, 
    grey = 1, 
    black = 2  
};


int c=1;
class graph
{
    int vertices;
    int edges;
    bool directed;
    vector<list<int>> adjList;
    COLORS *color;
    int *parent;
    int *distance;
    int *startingTime;
    int *finishingTime;
    vector<int> low;
    vector<bool> articulationPoints;
    int time;
    stack<int> topoOrderStack;
    bool hasCycle;
    int *comp;

public:
    graph(int vertices, int edges, bool ifDirected)
    {
        this->vertices = vertices;
        this->edges = edges;
        adjList.resize(vertices);
        directed = ifDirected;
        color = new COLORS[vertices];
        parent = new int[vertices];
        distance = new int[vertices];
        startingTime = new int[vertices];
        finishingTime = new int[vertices];
        low.resize(vertices + 1);
        articulationPoints.resize(vertices);
        time = 1;
        hasCycle = false;
        comp = new int[vertices];
    }

    void defineGraph()
    {
        for (int i = 0; i < edges; i++)
        {
            int u, v;
            cin >> u >> v;
            addEdge(u, v);
            // cout<<u<<" "<<v<<endl;
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
                low[v] = INT_MAX;
                comp[i]=1;
            }
        }
    }

    void DFS()
    {
        for(int i=0; i<vertices; i++)        
        {
            adjList[i].sort();
        }
        
        initialize();

        for (int i = 0; i < vertices; i++) 
            if (color[i] == white)
           {     DFS_Visit(i);
                c++;
           }
    }

private:
    void DFS_Visit(int u)
    {
        comp[u]=c;
        color[u] = grey;
        startingTime[u] = time;
        time++;
        int children = 0;
        for (auto v : adjList[u])
        {
            if (color[v] == grey)
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
        finishingTime[u] = time;
        time++;
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

    void printStartingTime()
    {
        cout << "\nentering time \n";
        for (int i = 1; i <= vertices; i++)
            cout << i << " : " << startingTime[i] << "\n";
    }

    void printFinishingTime()
    {
        cout << "\nleaving time \n";
        for (int i = 1; i <= vertices; i++)
            cout << i << " : " << finishingTime[i] << "\n";
    }

    bool isCycle()
    {
        return hasCycle;
    }

public:
    void print()
    {
        for(int i=0; i<vertices; i++)
        {
            cout<<i<<" : "<<comp[i]<<" "<<startingTime[i]<<" "<<finishingTime[i]<<endl;
        }
    }
};

int main()
{
    freopen("input.in", "r", stdin);
    freopen("output.in", "w", stdout);
    int m, n;
    cin>>m>>n;
    graph g(m, n, false); // starts from 0
    g.defineGraph();
    g.DFS();
    g.print();


    return 0;
}
