#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> findTerminalNodes(vector<vector<int>> &graph)
{
    vector<int> termNodes;
    for (int i = 0; i < graph.size(); i++)
    {
        if (graph[i].size() == 0)
            termNodes.push_back(i);
    }
    // for(auto v: termNodes)
    // {
    //     cout<<v<<" ";
    // }
    // cout<<endl;
    return termNodes;
}

enum COLORS
{
    white = 0,
    grey = 1,
    black = 2
};

bool BFS(int source, vector<vector<int>> &graph, vector<int> &termNodes)
{
    COLORS color[graph.size()];
    int parent[graph.size()];
    int distance[graph.size()];

    for (int i = 0; i < graph.size(); i++)
    {
        color[i] = white;
        for (auto v : graph[i])
        {
            color[v] = white;
            parent[v] = INT_MIN;
            distance[v] = INT_MAX;
        }
    }

    queue<int> grey_vert;
    grey_vert.push(source);
    color[source] = grey;
    distance[source] = 0;

    while (!grey_vert.empty())
    {
        int u = grey_vert.front();
        color[u] = grey;
        grey_vert.pop();

        for (auto v : graph[u])
        {
            if (color[v] == white)
            {
                color[v] = grey;
                distance[v] = distance[u] + 1;
                parent[v] = u;
                grey_vert.push(v);
            }
        }
        color[u] = black;
    }

    for (auto v : termNodes)
    {
        if (color[v] != white)
        {
            cout << source << "  is safe\n";
            return true;
        }
    }
    cout << source << "  is not safe\n";
    return false;
}

vector<int> eventualSafeNodes(vector<vector<int>> &graph)
{
    vector<int> termNodes = findTerminalNodes(graph);
    vector<int> safeNodes;
    
    for (auto v : termNodes)
    {
        safeNodes.push_back(v);
    }

    for (int i = 0; i < graph.size(); i++)
    {
        for (auto u : graph[i])
        {
            if (BFS(u, graph, termNodes))
                safeNodes.push_back(u);
        }
    }
    sort(safeNodes.begin(), safeNodes.end());
    return safeNodes;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    return 0;
}