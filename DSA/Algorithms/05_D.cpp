#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define debug(x) cerr << (#x) << ' ' << x << endl;
char graphmat[100 + 1][100 + 1];
vector<char> blocks(100+1);

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
    graph(int vertices, bool ifDirected)
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
        c = 0;
        in = new int[vertices + 1];
        out = new int[vertices + 1];
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
        for (int i = 0; i < vertices; i++)
        {
            indegreesArray.push_back(make_pair(i, in[i]));
            outdegreesArray.push_back(make_pair(i, out[i]));
        }
    }

private:
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
                comp[i] = 1;
            }
        }
    }

public:
    void DFS()
    {
        for (int i = 0; i < vertices; i++)
        {
            if (color[i] == white and blocks[i]!='#')
            {
                DFS_Visit(i);
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

private:
    static bool cmp(pair<int, int> &a, pair<int, int> &b) // this is inside graph class that's why u gotta use static here
    {
        return a.second <= b.second;
    }

public:
    int totalConnectedComp()
    {
        DFS();
        return c;
    }
};

bool valid(int i, int j, int m, int n)
{
    return i >= 0 and i < m and j >= 0 and j < n;
}

int main()
{

    int m, n;
    cin >> m >> n;
    int k=0;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> graphmat[i][j];
            blocks[i * n + j] = graphmat[i][j];
        }
    }
    graph g(m * n, false);

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (graphmat[i][j] == '.')
            {
                if (valid(i - 1, j, m, n))
                {
                    if (graphmat[i - 1][j] == '.')
                        g.addEdge(i * n + j, (i - 1) * n + j);
                }
                if (valid(i, j - 1, m, n))
                {
                    if (graphmat[i][j - 1] == '.')
                        g.addEdge(i * n + j, i * n + j - 1);
                }
            }
        }
    }

    cout << g.totalConnectedComp() << endl;

    return 0;
}
