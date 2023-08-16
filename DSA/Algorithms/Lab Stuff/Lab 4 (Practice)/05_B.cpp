#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

typedef pair<int, int> iPair;

enum COLORS
{
    white = 0, // not visited (not explored)
    grey = 1,  // visited but their neighbours are not visited (partially explored)
    black = 2  // visited along with all the neighbours (fully explored)
};

class triplet
{
public:
    int u, v, weight;
};

class graph
{
    vector<list<pair<int, int>>> adjList;
    int vertices;
    int edges;
    bool directed;
    COLORS *color;
    int *parent;
    int *distance;

public:
    graph(int vertices, int edges, bool ifDirected)
    {
        this->vertices = vertices;
        this->edges = edges;
        adjList.resize(vertices);
        directed = ifDirected;
        color = new COLORS[vertices];
        parent = new int[vertices];
        distance = new int[vertices];
    }

    void defineGraph()
    {
        for (int i = 0; i < edges; i++)
        {
            int u, v, weight;
            cin >> u >> v >> weight;
            addEdge(u, v, weight);
        }
    }

    void addEdge(int u, int v, int weight)
    {
        adjList[u].push_back({v, weight});
        if (!directed)
            adjList[v].push_back({u, weight});
    }

    void printGraph()
    {
        for (int i = 0; i < vertices; i++)
        {
            cout << i << " : ";
            for (auto v : adjList[i])
            {
                cout << v.first << " (" << v.second << "), ";
            }
            cout << endl;
        }
    }

    static bool compareSuper(pair<int, int> &a, pair<int, int> &b)
    {
        return a.second <= b.second;
    }

    void dijkstra(int source, int destination)
    {
        // initialize loop
        for (int i = 0; i < vertices; i++)
        {
            color[i] = white;
            for (auto v : adjList[i])
            {
                color[v.first] = white;
                parent[v.first] = INT_MIN;
                distance[v.first] = 1e7 + 9;
            }
            adjList[i].sort(compareSuper);
        }

        priority_queue<iPair, vector<iPair>> minHeap;
        minHeap.push(make_pair(source, 0));
        distance[source] = 0;
        while (!minHeap.empty())
        {
            int u = minHeap.top().first; // first is the vertex, second is the distance
            minHeap.pop();

            for (auto node : adjList[u])
            {
                int v = node.first;
                int weight = node.second;
                if (distance[v] > distance[u] + weight)
                {
                    distance[v] = distance[u] + weight;
                    minHeap.push(make_pair(v, distance[v])); // v = vertex and weight = edge weight between u and v
                    parent[v] = u;
                }
            }
        }
        printShortestPath(source, destination);
    }

public:
    void printShortestPath(int source, int destination)
    {
        // cout<<source<<" "<<destination<<endl;
        if (source == destination)
        {
            cout << source << " ";
        }
        else if (parent[destination] == INT_MIN)
        {
            cout << "No path" << endl;
        }
        else
        {
            printShortestPath(source, parent[destination]);
            cout << destination << " ";
        }
    }
};

int main()
{
    int m, n;
    cin >> m >> n;
    graph g(m, n, false); // starts from 0
    g.defineGraph();
    g.dijkstra(0, 1);
    return 0;
}