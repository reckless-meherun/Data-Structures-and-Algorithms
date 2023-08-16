#include <bits/stdc++.h>
using namespace std;

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
    vector<vector<int>> biconnectedComponents;
    vector<pair<int, int>> bridges;

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

public:
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

public:
    vector<pair<int, int>> findBridges()
    {
        DFS();
        for (auto v : bridges)
            cout << v.first << " " << v.second << "\n";
        cout << "\n";
        return bridges;
    }
    void findBiconnectedComponentsUtil(int u, int &time, int p, stack<pair<int, int>> &st)
    {
        color[u] = grey;
        startingTime[u] = low[u] = time;
        time++;

        int children = 0;
        for (auto v : adjList[u])
        {
            if (v == p)
                continue;

            if (color[v] == white)
            {
                st.push({u, v});
                children++;

                findBiconnectedComponentsUtil(v, time, u, st);

                low[u] = min(low[u], low[v]);

                if (low[v] >= startingTime[u])
                {
                    vector<int> component;
                    while (!st.empty() && st.top() != make_pair(u, v))
                    {
                        component.push_back(st.top().first);
                        component.push_back(st.top().second);
                        st.pop();
                    }
                    component.push_back(st.top().first);
                    component.push_back(st.top().second);
                    st.pop();

                    biconnectedComponents.push_back(component);
                }
            }
            else if (startingTime[v] < startingTime[u])
            {
                st.push({u, v});
                low[u] = min(low[u], startingTime[v]);
            }
        }
    }

    vector<vector<int>> findBiconnectedComponents()
    {
        for (int i = 0; i < vertices; i++)
        {
            color[i] = white;
            parent[i] = -1;
        }

        stack<pair<int, int>> st;
        int time = 0;

        for (int i = 0; i < vertices; i++)
        {
            if (color[i] == white)
            {
                findBiconnectedComponentsUtil(i, time, -1, st);
            }

            while (!st.empty())
            {
                vector<int> component;
                component.push_back(st.top().first);
                component.push_back(st.top().second);
                st.pop();
                biconnectedComponents.push_back(component);
            }
        }

        return biconnectedComponents;
    }
};

static bool compare(pair<int, int> &a, pair<int, int> &b) // this is inside graph class that's why u gotta use static here
{
    if (a.first == b.first)
        return a.second <= b.second;
    return a.first <= b.first;
}

int main()
{
    int m, n;
    cin >> m >> n;

    graph g(m, n, false);
    g.defineGraph();

    vector<vector<int>> biconnectedComponents = g.findBiconnectedComponents();
    vector<vector<pair<int, int>>> bcc(m);
    int c = 0;
    // cout << "Biconnected Components:" << endl;

    for (const auto &component : biconnectedComponents)
    {
        for (size_t i = 0; i < component.size(); i += 2)
        {
            // cout << component[i] << "-" << component[i + 1];
            bcc[c].push_back({min(component[i], component[i + 1]), max(component[i], component[i + 1])});
            // if (i + 2 < component.size())
            // {
            //     // cout << "\n";
            // }
        }

        sort(bcc[c].begin(), bcc[c].end(), compare);
        c++;
    }

    sort(bcc.begin(), bcc.end());

    int i = 0;
    for (auto row : bcc)
    {
        if (row.size() != 0)
        {
            for (auto col : row)
            {
                cout << col.first << " " << col.second << "\n";
            }
            if (i != bcc.size() - 1)
                cout << "-\n";
        }
        i++;
    }

    return 0;
}
