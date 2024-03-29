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
    stack<int> topoOrderStack;
    bool hasCycle;
    int totalSCC = 0;

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
        hasCycle = false;
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

    void DFS(int source)
    {
        initialize();
        DFS_Visit(source); // u don't need to run an extra loop, the recursion will visit all the vertices automatically
    }

    void DFS(vector<pair<int, int>> &ordered_node)
    {
        initialize();

        // printGraph();

        for (auto a : ordered_node)
        {
            // if(a.first == 5) cout<<"color of 5 "<<color[a.first]<<endl;
            if (color[a.first] == white)
            {
                // cout<<"white node "<<a.first<<endl;
                DFS_Visit(a.first);
                cout << "\n";
                totalSCC++;
            }
        }
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
        //cout << "entering Vertex : " << u << " pre V : " << time << endl;
        startingTime[u] = low[u] = time;
        time++;
        int children = 0;
        for (auto v : adjList[u])
        {
            // cout << "Parent : " << u << " Child : " << v << endl;
            /** Action on ANY child (v) of vertex (u) before entering the child */
            if (color[v] == grey)
                hasCycle = true;
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
        vector<list<int>> adjList2(vertices + 1);
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

    int pos[1000000];

public:
    vector<pair<int, int>> topologicalSort()
    {
        for (int i = 0; i < vertices; i++)
        {
            startingTime[i] = 0;
            finishingTime[i] = 0;
        }
        DFS();
        if (hasCycle)
            cout << "the sorting is not topological" << endl;
        int indx = 0;
        vector<pair<int, int>> sortedFinishTime;
        for (int i = 0; i < vertices; i++)
        {
            sortedFinishTime.push_back(make_pair(i, finishingTime[i]));
        }
        sort(sortedFinishTime.begin(), sortedFinishTime.end(), cmp);
        // cout << endl
        //      << "topological sort : vertex - finishing time \n";

        while (!topoOrderStack.empty()) // have to do it
            topoOrderStack.pop();

        for (auto v : sortedFinishTime)
        {
            cout << v.first << "\n";
            topoOrderStack.push(v.first);
            pos[v.first] = indx;
            indx++;
        }
        return sortedFinishTime;
    }

    bool detectCycleWithTopoSort()
    {
        topologicalSort();
        int arr[vertices + 1];
        int i = 1;
        while (!topoOrderStack.empty())
        {
            arr[i++] = topoOrderStack.top();
            topoOrderStack.pop();
        }
        for (int i = 0; i < vertices; i++)
        {
            for (auto v : adjList[i])
            {
                if (pos[i] > pos[v])
                {
                    return true;
                }
            }
        }
        return false;
    }

    void findSCC()
    {
        vector<pair<int, int>> orderedNodes = topologicalSort();
        transpose();
        cout << "\nhmmmm followings are the SCC\n"
             << endl;
        DFS(orderedNodes);
        transpose();
    }

    int totalNumberSCC()
    {
        findSCC();
        return totalSCC;
    }

    void printLowValues()
    {
        for (int i = 0; i < vertices; i++)
            cout << i << " : " << low[i] << "\n";
        cout << "\n";
    }

    bool isCycle()
    {
        return hasCycle;
    }
};

int main()
{
    int m, n;
    cin >> m >> n;
    graph g(m, n, true); 
    g.defineGraph();
    g.topologicalSort();

    return 0;
}