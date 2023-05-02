#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

enum COLORS
{
    white = 0, // not visited (not explored)
    grey = 1,  // visited but their neighbours are not visited (partially explored)
    black = 2  // visited along with all the neighbours (fully explored)
};

class graph
{
    int vertices;
    int edges;
    bool directed;
    vector<list<int>> adjList;
    COLORS *color;
    int *parent;
    int *distance;

public:
    graph(int vertices, int edges, bool ifDirected)
    {
        this->vertices = vertices;
        this->edges = edges;
        adjList.resize(vertices+1);
        directed = ifDirected;
        color = new COLORS[vertices+1];
        parent = new int[vertices + 1];
        distance = new int[vertices + 1];
    }

    void defineGraph()
    {
        for (int i = 1; i <= edges; i++)
        {
            int u, v;
            cin >> u >> v;
            addEdge(u, v);
            cout<<u<<" "<<v<<endl;
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

    void BFS(int source)
    {
        // initialize loop
        for (int i = 1; i <= vertices; i++)
        {
            for (auto v : adjList[i])
            {
                color[v] = white;
                parent[v] = INT_MIN;
                distance[v] = INT_MAX;
            }
        }

        queue<int> grey_ver; // vertices that are grey/visited

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
            color[u] = black; // cause it has been fully explored
        }
    }

    void DFS(int source)
    {
        // initialize loop
        for (int i = 1; i <= vertices; i++)
        {
            for (auto v : adjList[i])
            {
                color[v] = white;
                parent[v] = INT_MIN;
                distance[v] = INT_MAX;
            }
        }

        for (int u = 1; u <= vertices; u++)
        {
            if (color[u] == white)
            {
                DFS_Visit(u);
            }
        }
    }

    void DFS_Visit(int u)
    {
        /** Action on a vertex (u) after entering the vertex */
        color[u] = grey;
        cout<<"Vertex : "<<u<<endl;
        for (auto v : adjList[u])
        {
            cout<<"Parent : "<<u<<" Child : "<<v<<endl;
            /** Action on ANY child (v) of vertex (u) before entering the child */
            if (color[v] == white)
            {
                /** Action on an unvisited/white child (v) of vertex (u) before entering the child */
                color[v] = grey;
                distance[v] = distance[u] + 1;
                parent[v] = u;
                DFS_Visit(v);
                /** Action on the visited child (v) of vertex (u) after leaving the child */
            }
            /** Action on ANY VISITED child (v) of vertex (u) after leaving the child */
        }
        /** Action on a vertex (u) before leaving the vertex */
        color[u] = black;
    }

    void printShortestPath(int source, int destination)
    {
        //cout<<source<<" "<<destination<<endl;
        if (source == destination)
        {
            cout << source << " ";
        }
        else if (parent[destination] == INT_MIN)
        {    
            cout << "No path" << endl;
        }
        else
        {
            printShortestPath(source, parent[destination]);
            cout << destination << " ";
        }
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
    graph g(6, 8, false);
    g.defineGraph();
    g.printGraph();
    g.BFS(1);
    g.DFS(1);
    g.printShortestPath(2, 1);
    
    return 0;
}