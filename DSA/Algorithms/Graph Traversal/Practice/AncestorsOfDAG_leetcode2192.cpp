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

COLORS color[1000000];
int dist[1000000];
int parent[1000000];
vector<vector<int>> ancestors(1001);

void transpose(int n, vector<vector<int>> &graph)
{
    vector<vector<int>> adjList2(n);
    for (int i = 0; i < n; i++)
    {
        for (auto v : graph[i])
        {
            adjList2[v].push_back(i);
        }
    }
    graph = adjList2;
}

void DFS_Visit(int u, vector<vector<int>> &graph)
{
    cout << u << " has color " << color[u] << "\n";
    for (auto v : graph[u])
    {
        cout << v << " has color " << color[v] << "\n";
    }
    /** Action on a vertex (u) after entering the vertex */
    color[u] = grey;
    // debug(u);
    //  cout << endl
    //       << u << " : ";
    for (auto v : graph[u])
    {
        // cout << v << " has color "<<color[v]<<"\n";
        // debug(color[v]);
        if (color[v] != white)
        {
            for (auto x : ancestors[v])
            {
                ancestors[u].push_back(x);
            }
        }
        if (color[v] == white)
        {
            cout << v << " ";
            ancestors[u].push_back(v);
            /** Action on an unvisited/white child (v) of vertex (u) before entering the child */
            color[v] = grey;
            dist[v] = dist[u] + 1;
            parent[v] = u;

            DFS_Visit(v, graph);
        }
    }
    color[u] = black;
    cout << endl;
}

void DFS(int n, vector<vector<int>> &graph)
{
    // cout << "dfs started ";
    for (int i = 0; i < n; i++)
    {
        color[i] = white;
        for (auto v : graph[i])
        {
            color[v] = white;
            parent[v] = INT_MIN;
            dist[v] = INT_MAX;
        }
    }

    // cout << " init";
    for (int i = 0; i < n; i++) // in case the graph is a forest (disconnected)
    {
        if (color[i] == white)
        {
            // cout << "dfs callll";
            DFS_Visit(i, graph);
        }
    }

    // cout << "dfs done ";
    for (int i = 0; i < n; i++)
    {
        // for (auto v : graph[i])
        // {
        //     if (color[v] != white)
        //     {
        //         ancestors[i].push_back(v);
        //     }
        // }
        sort(ancestors[i].begin(), ancestors[i].end());
    }
    // cout << "ancs sorted ";
}

vector<vector<int>> getAncestors(int n, vector<vector<int>> &edge)
{
    vector<vector<int>> e(edge.size());
    vector<vector<int>> graph(n);
    
    for (int i = 0; i < edge.size(); i++)
    {
        // cout << edge[i][0] << " : " << edge[i][1] << endl;
        graph[edge[i][0]].push_back(edge[i][1]);
    }

    for (int i = 0; i < n; i++)
    {
        cout << i << " : ";
        for (auto v : graph[i])
            cout << v << " ";
        cout << "\n";
    }
    transpose(n, graph);
    cout << "after transpose\n";
    for (int i = 0; i < n; i++)
    {
        cout << i << " : ";
        for (auto v : graph[i])
        {
            cout << v << " ";
            ancestors[i].push_back(v);
        }
        cout << "\n";
    }
    cout << endl;
    DFS(n, graph);
    for (int i = 0; i < n; i++)
    {
        ancestors[i].erase(unique(ancestors[i].begin(), ancestors[i].end()), ancestors[i].end());
    }
    ancestors.resize(n);
    return ancestors;
}

int main()
{
    int m, n;
    cin >> m >> n;
    vector<vector<int>> edge(n);
    for (int i = 0; i < n; i++)
    {
        int a, b;
        cin >> a >> b;
        // cout<<a<<" "<<b<<"\n";
        edge[i].push_back(a);
        edge[i].push_back(b);
    }

    vector<vector<int>> x = getAncestors(m, edge);

    // cout << "here" << endl;

    for (int i = 0; i < n; i++)
    {
        cout << i << " : ";
        for (auto v : x[i])
            cout << v << " ";
        cout << "\n";
    }

    return 0;
}