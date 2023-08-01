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

void DFS_Visit(int u, vector<vector<int>> &graph)
{
    color[u] = grey;
    startTime[u] = Time;
    Time++;
    for (auto v : graph[u])
    {
        if (color[v] == white)
        {
            cout << v << " ";
            color[v] = grey;
            dist[v] = dist[u] + 1;
            parent[v] = u;

            DFS_Visit(v, graph);
        }
    }
    color[u] = black;
    endTime[u] = Time;
    Time++;
    cout << endl;
}

void DFS(int u, vector<vector<int>> &graph)
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
    // for (int i = 0; i < graph.size(); i++)
    // {
    //     for (auto v : graph[i])
    //     {
    //         if (color[v] == white)
    //         {
    //             DFS_Visit(i, graph);
    //         }
    //     }
    // }
    DFS_Visit(u, graph);
}

vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>> &prerequisites, vector<vector<int>> &queries)
{
    vector<vector<int>> graph(numCourses);
    vector<vector<int>> qList(numCourses);
    vector<bool> check(queries.size());

    for (int i = 0; i < prerequisites.size(); i++)
    {
        graph[prerequisites[i][0]].push_back(prerequisites[i][1]);
    }

    //DFS(graph);

    for (int i = 0; i < queries.size(); i++)
    {
        DFS(queries[i][0], graph);
        if (color[queries[i][1]] != white)
            check[i] = true;
        else
            check[i] = false;
    }
    return check;
}

int main()
{

    return 0;
}