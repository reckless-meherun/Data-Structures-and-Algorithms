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
    graph(int vertices, bool ifDirected)
    {
        this->vertices = vertices;
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

    // void defineGraph()
    // {
    //     for (int i = 0; i < edges; i++)
    //     {
    //         int u, v;
    //         cin >> u >> v;
    //         addEdge(u, v);
    //         // cout<<u<<" "<<v<<endl;
    //     }
    // }

    void inputAdjList()
    {
        for (int i = 0; i < vertices; i++)
        {
            int u, adjVnum = 1, v;
            string g, k;
            cin >> u >> g;
            k = g.substr(1, g.size() - 2);
            adjVnum = stoi(k);
            while (adjVnum--)
            {
                cin >> v;
                adjList[u].push_back(v);
            }
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
        color[u] = grey;
        startingTime[u] = low[u] = time;
        time++;
        int children = 0;

        for (auto v : adjList[u])
        {

            if (color[v] == white)
            {
                color[v] = grey;
                distance[v] = distance[u] + 1;
                parent[v] = u;
                children++; // increase the number of children of u

                DFS_Visit(v);
                low[u] = min(low[v], low[u]);

                if (low[v] > startingTime[u])
                    bridges.push_back({u, v});
            }
            else if (v != parent[u]) // visited but ignore child to parent edge
                low[u] = min(low[u], startingTime[v]);
        }
        color[u] = black;
        finishingTime[u] = time;
        time++;
    }

public:
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

    static bool cmp(pair<int, int> a, pair<int, int> b)
    {
        if (a.first != b.first)
            return a.first < b.first;
        else
            return a.second <= b.second;
    }

    vector<pair<int, int>> findBridges()
    {
        DFS();
        cout << bridges.size() << " critical links\n";
        sort(bridges.begin(), bridges.end(), cmp);
        for (auto v : bridges)
        {
            cout << min(v.first, v.second) << " - " << max(v.first, v.second) << "\n";
        }
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
    int test;
    cin >> test;
    int i = 1;
    while (test--)
    {
        int m;
        cin >> m;
        graph g(m, false);
        g.inputAdjList();
        cout << "Case " << i << ":\n";
        g.findBridges();
        i++;
    }
    return 0;
}