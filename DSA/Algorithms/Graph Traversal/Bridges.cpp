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
    vector<pair<int, int>> bridges;
    int time;

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
        low.resize(vertices);
        // bridges.resize(vertices); // highest number of bridge can be n-1 when there are n vertices
        time = 1;
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
            }
        }
    }

    void BFS(int source)
    {
        initialize();

        queue<int> grey_ver; // vertices that are grey/visited
        // Queue grey_ver;

        color[source] = grey;
        distance[source] = 0;
        grey_ver.push(source);
        // grey_ver.enqueue(source);

        while (!grey_ver.empty())
        {
            int u = grey_ver.front();
            // int u = grey_ver.peek();
            grey_ver.pop();
            // grey_ver.dequeue();
            for (auto v : adjList[u])
            {
                if (color[v] == white)
                {
                    color[v] = grey;
                    distance[v] = distance[u] + 1;
                    parent[v] = u;
                    grey_ver.push(v);
                    // grey_ver.enqueue(v);
                }
            }
            color[u] = black; // cause it has been fully explored
        }
    }

    void DFS(int source)
    {
        initialize();
        DFS_Visit(source); // u don't need to run an extra loop, the recursion will visit all the vertices automatically
    }

    void DFS()
    {
        initialize();

        for (int i = 0; i < vertices; i++) // in case the graph is a forest (disconnected)
            if (color[i] == white)
                DFS_Visit(i);
    }

private:
    void DFS_Visit(int u)
    {
        /** Action on a vertex (u) after entering the vertex */
        color[u] = grey;
        // cout << "entering Vertex : " << u << " pre V : " << time << endl;
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

                if (low[v] > startingTime[u])
                    bridges.push_back({u, v});
            }
            /** Action on ANY VISITED child (v) of vertex (u) after leaving the child */
            else if (v != parent[u]) // visited but ignore child to parent edge
                low[u] = min(low[u], startingTime[v]);
        }
        /** Action on a vertex (u) before leaving the vertex */
        color[u] = black;
        finishingTime[u] = time;
        // cout << "leaving Vertex : " << u << " post V : " << time << endl;
        time++;
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

    void printStartingTime()
    {
        cout << "\nentering time \n";
        for (int i = 0; i < vertices; i++)
            cout << i << " : " << startingTime[i] << "\n";
    }

    void printFinishingTime()
    {
        cout << "\nleaving time \n";
        for (int i = 0; i < vertices; i++)
            cout << i << " : " << finishingTime[i] << "\n";
    }

    void transpose()
    {
        vector<list<int>> adjList2(vertices);
        if (directed)
        {
            for (int i = 0; i < vertices; i++)
            {
                for (auto v : adjList[i])
                {
                    adjList2[v].push_back(i);
                }
            }
            adjList = adjList2;
        }
    }

private:
    static bool cmp(pair<int, int> &a, pair<int, int> &b) // this is inside graph class that's why u gotta use static here
    {
        return a.second >= b.second;
    }

public:
    vector<pair<int, int>> topologicalSort()
    {
        vector<pair<int, int>> sortedFinishTime;
        for (int i = 0; i < vertices; i++)
        {
            sortedFinishTime.push_back(make_pair(i, finishingTime[i]));
        }
        sort(sortedFinishTime.begin(), sortedFinishTime.end(), cmp);
        cout << endl;
        for (auto v : sortedFinishTime)
        {
            cout << v.first << " " << v.second << "\n";
        }
        return sortedFinishTime;
    }

    void findSCC(int source)
    {
        DFS(source);
        vector<pair<int, int>> orderedNodes = topologicalSort();
        transpose();
        // cout<<orderedNodes[0].first<<endl;
        // g.printGraph();
        // cout << "hmmmm followings are the SCC" << endl;
        for (int i = 0; i < vertices; i++)
        {
            DFS(orderedNodes[i].first);
            cout << "\n";
        }
    }

    vector<pair<int, int>> findBridges()
    {
        DFS();
        for (auto v : bridges)
            cout << v.first << " " << v.second << "\n";
        cout << "\n";
        return bridges;
    }

    void printLowValues()
    {
        for (int i = 0; i < vertices; i++)
            cout << i << " : " << low[i] << "\n";
        cout << "\n";
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    graph g(8, 8, false); // starts from 1
    g.defineGraph();

    vector<pair<int, int>> v = g.findBridges();

    return 0;
}