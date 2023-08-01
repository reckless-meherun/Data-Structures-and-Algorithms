/** accepted */

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
int Time = 1;
int startTime[100000];
int endTime[100000];
stack<int> order;
int backEdge = false;

void DFS_Visit(int u, vector<vector<int>> &graph)
{
    color[u] = grey;
    startTime[u] = Time;
    Time++;
    for (auto v : graph[u])
    {
        if (color[v] == grey)
        {
            backEdge = true;
            return;
        }
        if (color[v] == white)
        {
            // cout << v << " ";
            color[v] = grey;
            // dist[v] = dist[u] + 1;
            parent[v] = u;

            DFS_Visit(v, graph);
        }
    }
    color[u] = black;
    endTime[u] = Time;
    Time++;
    cout << endl;
    debug(u);
    order.push(u);
}

void DFS(vector<vector<int>> &graph)
{
    for (int i = 0; i < graph.size(); i++)
    {
        color[i] = white;
        for (auto v : graph[i])
        {
            color[v] = white;
            parent[v] = INT_MIN;
            dist[v] = INT_MAX;
        }
    }
    for (int i = 0; i < graph.size(); i++)
    {
        // debug(i);
        // debug(color[i]);
        if (color[i] == white)
        {
            DFS_Visit(i, graph);
        }
    }
}

vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites)
{
    vector<vector<int>> graph(numCourses);

    for (int i = 0; i < prerequisites.size(); i++)
    {
        graph[prerequisites[i][0]].push_back(prerequisites[i][1]);
    }
    // for (int i = 0; i < numCourses; i++)
    // {
    //     cout << i << " : ";
    //     for (auto v : graph[i])
    //     {
    //         cout << v << " ";
    //     }
    //     cout << endl;
    // }

    DFS(graph);
    vector<int> sorted;

    if (backEdge)
    {
        // debug(backEdge);
        // debug(sorted.size());
        return sorted;
    }
    if (prerequisites.size() == 0)
    {
        int i = 0;
        while (numCourses--)
        {
            sorted.push_back(i);
            i++;
        }
    }
    else
    {
        debug(sorted.size());
        while (!order.empty())
        {
            sorted.push_back(order.top());
            order.pop();
        }
        debug(sorted.size());
        reverse(sorted.begin(), sorted.end());
    }
    return sorted;
}

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> prerequisites(m);
    int i = 0;
    while (m--)
    {
        int a, b;
        cin >> a >> b;
        prerequisites[i].push_back(a);
        prerequisites[i++].push_back(b);
    }
    vector<int> x = findOrder(n, prerequisites);
    debug(x.size());
    for (int i = 0; i < x.size(); i++)
    {
        cout << x[i] << " ";
    }
    return 0;
}