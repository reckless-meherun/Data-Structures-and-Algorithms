#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define debug(x) cerr << (#x) << ' ' << x << endl;

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
    int c;
    int *in;
    int *out;

    vector<pair<int, int>> indegreesArray;
    vector<pair<int, int>> outdegreesArray;

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
        comp = new int[vertices + 1];
        c = 1;
        in = new int[vertices + 1];
        out = new int[vertices + 1];
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
        in[v]++;
        out[u]++;
        if (!directed)
        {
            adjList[v].push_back(u);
            in[u]++;
            out[v]++;
        }
    }

    void removeEdge(int u, int v)
    {
        adjList[u].remove(v);
    }

    void calculateDegrees()
    {
        for (int i = 1; i <= vertices; i++)
        {
            indegreesArray.push_back(make_pair(i, in[i]));
            outdegreesArray.push_back(make_pair(i, out[i]));
        }
    }

private:
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
                comp[i] = 1;
            }
        }
    }

public:
    void DFS(vector<pair<int, int>> &ordered_node)
    {
        initialize();
        for (auto a : ordered_node)
        {
            if (color[a.first] == white)
            {
                DFS_Visit(a.first);
                c++;
            }
        }
    }

private:
    void DFS_Visit(int u)
    {
        comp[u] = c;
        color[u] = grey;
        startingTime[u] = time;
        time++;
        int children = 0;
        for (auto v : adjList[u])
        {
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

private:
    static bool cmp(pair<int, int> &a, pair<int, int> &b) // this is inside graph class that's why u gotta use static here
    {
        return a.second <= b.second;
    }

public:
    int totalConnectedComp()
    {
        calculateDegrees();
        sort(indegreesArray.begin(), indegreesArray.end(), cmp);
        DFS(indegreesArray);
        return *max_element(comp, comp + vertices + 1);
    }
};

int main()
{
    int test;
    cin >> test;
    while (test--)
    {
        int m, n;
        cin >> m >> n;
        graph g(m, n, true); // starts from 1
        g.defineGraph();
        cout << g.totalConnectedComp() << endl;
    }

    return 0;
}
