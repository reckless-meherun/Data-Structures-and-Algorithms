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
    vector<int> distance;
    vector<triplet> edgeList;
    vector<vector<int>> shortestPath;

public:
    graph(int vertices, int edges, bool ifDirected)
    {
        this->vertices = vertices;
        this->edges = edges;
        adjList.resize(vertices);
        edgeList.resize(edges);
        shortestPath.resize(vertices);
        directed = ifDirected;
        color = new COLORS[vertices];
        parent = new int[vertices];
        distance.resize(vertices);
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
        edgeList.push_back({u, v, weight});
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

private:
    void initialize(int source)
    {
        for (int i = 0; i < vertices; i++)
        {
            distance[i] = INT_MAX;
            parent[i] = INT_MIN;
        }
        distance[source] = 0;
    }

    bool relax(int u, int v, int weight)
    {
        if (distance[v] > distance[u] + weight)
        {
            distance[v] = distance[u] + weight;
            parent[v] = u;
            if (v == 1)
                cout << u << " " << distance[1] << "\n";
            if (v == 2)
                cout << u << " " << distance[2] << "\n";
            return true;
        }
        return false;
    }

public:
    bool bellman_ford(int source)
    {
        initialize(source);

        for (int i = 0; i < vertices - 1; i++)
        {
            for (auto e : edgeList)
            {
                relax(e.u, e.v, e.weight);
            }
        }

        // checking negative cycles
        for (auto e : edgeList)
        {
            if (relax(e.u, e.v, e.weight))
            {
                cout << "Negative cycle exists; Bellman_Ford is not possible\n";
                return false;
            }
        }

        // printing the distances from source

        cout << "Distance of all vertices from source : " << source << "\n";
        for (int i = 0; i < vertices; i++)
        {
            cout << source << " - " << i << " : \nPath : ";
            printShortestPath(source, i);
            cout << "\nCost : ";
            cout << distance[i] << "\n";
            cout << "\n";
        }
        return true;
    }

    void dijkstra(int source)
    {
        // initialize loop
        for (int i = 0; i < vertices; i++)
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

        cout << "\nShortest path from source to vertices through dijkstra\n";
        for (int i = 0; i < vertices; i++)
        {
            cout << source << " - " << i << " : \nPath : ";
            printShortestPath(source, i);
            cout << "\nCost : ";
            cout << distance[i] << "\n";
            cout << "\n";
        }
    }

private:
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

public:
    void johnson()
    {
        if (!bellman_ford(0))
        {
            cout << "Negative cycle exists so shortest path is not possible" << endl;
            return;
        }

        auto bellDistance = distance;
        for (int u = 0; u < vertices; u++)
        {
            for (auto v : adjList[u])
            {
                int &w = v.second;
                w = w + bellDistance[u] - bellDistance[v.first];
            }
        }

        vector<vector<int>> apsp(vertices);
        // dijkstra(0);
        // dijkstra(1);
        // dijkstra(2);
        // dijkstra(3);

        for (int u = 0; u < vertices; u++)
        {
            dijkstra(u);
            cout << "done\n";
            apsp[u] = distance;
        }
        printPath(apsp);
    }

private:
    void printPath(vector<vector<int>> apsp)
    {
        for (int u = 0; u < vertices; u++)
        {
            for (int v = 0; v < vertices; v++)
            {
                if (apsp[u][v] == INT_MAX)
                    cout << "inf"
                         << " ";
                else
                    cout << apsp[u][v] << " ";
            }
            cout << "\n";
        }
    }
};

int main()
{
    graph g(4, 4, true); // starts from 0
    g.defineGraph();
    g.johnson();
    return 0;
}