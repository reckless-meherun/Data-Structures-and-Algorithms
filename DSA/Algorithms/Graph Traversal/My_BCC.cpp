#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <algorithm>
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
    int totalSCC=0;
    vector<vector<int>> biconnectedComponents;
    

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
public:

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

int main()
{
    int m,n;
    cin>>m>>n;

    graph g(m, n, false);
    g.defineGraph();

    vector<vector<int>> biconnectedComponents = g.findBiconnectedComponents();

    cout << "Biconnected Components:" << endl;

    for (const auto &component : biconnectedComponents)
    {
        for (size_t i = 0; i < component.size(); i += 2)
        {
            cout << component[i] << "-" << component[i + 1];
            if (i + 2 < component.size())
                cout << " ";
        }
        cout << endl;
    }

    return 0;
}
