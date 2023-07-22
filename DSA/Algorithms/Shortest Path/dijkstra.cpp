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
        adjList.resize(vertices + 1);
        directed = ifDirected;
        color = new COLORS[vertices + 1];
        parent = new int[vertices + 1];
        distance = new int[vertices + 1];
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

    // void removeEdge(int u, int v)
    // {
    //     adjList[u].remove({v, weight});
    // }

    // bool isConnected(int u, int v)
    // {
    //     // sort(adjList[u].begin(), adjList[u].end());
    //     adjList[u].sort();
    //     adjList[v].sort();
    //     return (binary_search(adjList[u].begin(), adjList[u].end(), v)) or (binary_search(adjList[v].begin(), adjList[v].end(), u));
    // }

    int outDegree(int u)
    {
        return adjList[u].size();
    }

    int inDegree(int u)
    {
        if (!directed)
            return outDegree(u);

        int inD = 0;
        for (int i = 1; i <= vertices; i++)
        {
            for (auto v : adjList[i]) /** inDegree : how many times u is in the lists of each vertex list */
            {
                if (v.first == u)
                    inD++;
            }
        }

        return inD;

        /** can be done with binary search as well */
        /** inD = 0;
        for (int i = 1; i <= vertices; i++)
        {
            sort(adjList[i].begin(), adjList[i].end());
            if(binary_search(adjList[i].begin(), adjList[i].end(), u))
                inD++;
        }
        return inD; */
    }

    void printGraph()
    {
        for (int i = 1; i <= vertices; i++)
        {
            cout << i << " : ";
            for (auto v : adjList[i])
            {
                cout << v.first << " (" << v.second << "), ";
            }
            cout << endl;
        }
    }

    void dijkstra(int source)
    {
        // initialize loop
        for (int i = 1; i <= vertices; i++)
        {
            color[i] = white;
            for (auto v : adjList[i])
            {
                color[v.first] = white;
                parent[v.first] = INT_MIN;
                distance[v.first] = INT_MAX;
            }
        }

        priority_queue<iPair, vector<iPair>> minHeap;
        minHeap.push(make_pair(source, 0));
        distance[source] = 0;
        while (!minHeap.empty())
        {
            int u = minHeap.top().first; // first is the vertex, second is the distance
            minHeap.pop();

            for (auto v : adjList[u])
            {
                if (distance[v.first] > distance[u] + v.second)
                {
                    distance[v.first] = distance[u] + v.second;
                    minHeap.push(make_pair(v.first, distance[v.first])); // v.first = vertex and v.second = edge weight between u and v.first
                    parent[v.first] = u;
                }
            }
        }

        cout << "Shortest path from source to vertices through dijkstra\n";
        for (int i = 1; i <= vertices; i++)
            cout << source << " to " << i << " - > " << distance[i] << "\n";
    }
};

int main()
{
    freopen("input.in", "r", stdin);
    freopen("output.in", "w", stdout);
    graph g(9, 14, false); // starts from 1
    g.defineGraph();
    // g.printGraph();
    g.dijkstra(1);
    // g.printShortestPath(3,1);
    return 0;
}