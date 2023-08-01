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
    int *startingTime;
    int *finishingTime;
    vector<int> low;
    vector<bool> articulationPoints;
    int time;

public:
    graph(int vertices, int edges, bool ifDirected)
    {
        this->vertices = vertices;
        this->edges = edges;
        adjList.resize(vertices + 1);
        directed = ifDirected;
        color = new COLORS[vertices + 1];
        parent = new int[vertices + 1];
        distance = new int[vertices + 1];
        startingTime = new int[vertices + 1];
        finishingTime = new int[vertices + 1];
        low.resize(vertices + 1);
        articulationPoints.resize(vertices + 1);
        time = 1;
    }

    void defineGraph()
    {
        for (int i = 1; i <= edges; i++)
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
        for (int i = 1; i <= vertices; i++)
        {
            color[i] = white;
            for (auto v : adjList[i])
            {
                color[v] = white;
                parent[v] = INT_MIN;
                distance[v] = INT_MAX;
                low[v] = INT_MAX;
            }
        }
    }

    void DFS(int source) // in case the graph is not a forest (all connected)
    {
        initialize();
        DFS_Visit(source); // u don't need to run an extra loop, the recursion will visit all the vertices automatically
    }

    void DFS() // in case the graph is a forest (disconnected)
    {
        initialize();

        for (int i = 1; i <= vertices; i++)
            if (color[i] == white)
                DFS_Visit(i);
    }

private:
    void DFS_Visit(int u)
    {
        /** Action on a vertex (u) after entering the vertex */
        color[u] = grey;
        //cout << "entering Vertex : " << u << " pre V : " << time << endl;
        startingTime[u] = low[u] = time;
        time++;
        int children = 0;

        for (auto v : adjList[u])
        {
            // cout<<"Parent : "<<u<<" Child : "<<v<<endl;
            /** Action on ANY child (v) of vertex (u) before entering the child */

            if (color[v] == white)
            {
                /** Action on an unvisited/white child (v) of vertex (u) before entering the child */
                color[v] = grey;
                distance[v] = distance[u] + 1;
                parent[v] = u;
                children++; // increase the number of children of u

                DFS_Visit(v);

                /** Action on the visited child (v) of vertex (u) after leaving the child */
                low[u] = min(low[v], low[u]);

                if (parent[u] == INT_MIN and children > 1) // case 1 : u is a root
                    articulationPoints[u] = true;

                if (parent[u] != INT_MIN and low[v] >= startingTime[u]) // case 2 : at least one component will get separated
                    articulationPoints[u] = true;
            }
            /** Action on ANY VISITED child (v) of vertex (u) after leaving the child */
            else if (v != parent[u]) // visited but ignore child to parent edge
                low[u] = min(low[u], startingTime[v]);
        }
        /** Action on a vertex (u) before leaving the vertex */
        color[u] = black;
        finishingTime[u] = time;
        //cout << "leaving Vertex : " << u << " post V : " << time << endl;
        time++;
    }

public:
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

    vector<bool> findArticulationPoints()
    {
        DFS();
        // for (int i = 1; i <= vertices; i++)
        //     if (articulationPoints[i])
        //         cout << i << " ";
        // cout << "\n";
        return articulationPoints;
    }

    void printLowValues()
    {
        for (int i = 1; i <= vertices; i++)
            cout << i << " : " << low[i] << "\n";
        cout << "\n";
    }

    int countArticulationPoints()
    {
        findArticulationPoints();
        int count=0;
        for(int i=1; i<=vertices; i++)
        {
            if(articulationPoints[i])
                count++;
        }
        return count;
    }
};

int main()
{
    // while (1)
    // {
    //     int N;
    //     cin >> N;
    //     if (N == 0)
    //         break;

    //     while (N--)
    //     {
            int m, n;
            cin>>m>>n;
            graph g(m, n, false); // starts from 1
            g.defineGraph();
            // g.printGraph();

            cout<<g.countArticulationPoints()<<endl;
    //     }
    // }

    return 0;
}