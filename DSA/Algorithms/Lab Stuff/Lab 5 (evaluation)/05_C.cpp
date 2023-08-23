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
public:
    vector<list<pair<int, int>>> adjList;
    int vertices;
    int edges;
    bool directed;
    COLORS *color;
    int *parent;
    vector<vector<int>> parentDJ;
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
        parentDJ.resize(vertices, vector<int>(vertices));
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
        for (int i = 0; i < vertices + 1; i++)
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
            return true;
        }
        return false;
    }

    bool bellman_ford(int source)
    {
        initialize(source);

        for (int i = 0; i < vertices; i++)
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
                cout << "not possible\n";
                return false;
            }
        }

        // printing the distances from source

        // cout << "Distance of all vertices from source : " << source << "\n";
        // for (int i = 0; i < vertices + 1; i++)
        // {
        //     cout << source << " - " << i << " : \nPath : ";
        //     printShortestPath(source, i);
        //     cout << "\nCost : ";
        //     cout << distance[i] << "\n";
        //     cout << "\n";
        // }
        return true;
    }

    void dijkstra(int source)
    {
        // initialize loop
        for (int i = 0; i < vertices; i++)
        {
            color[i] = white;
            color[i] = white;
            distance[i] = INT_MAX;
            parentDJ[source][i] = INT_MIN;
        }

        priority_queue<iPair, vector<iPair>> minHeap;
        minHeap.push(make_pair(source, 0));
        distance[source] = 0;
        while (!minHeap.empty())
        {

            int u = minHeap.top().first; // first is the vertex, second is the distance
            minHeap.pop();
            // cout<<u<<endl;
            if (color[u] != white)
                continue;
            color[u] = grey;

            for (auto node : adjList[u])
            {
                int v = node.first;
                int weight = node.second;
                if (distance[v] > distance[u] + weight)
                {
                    distance[v] = distance[u] + weight;
                    minHeap.push(make_pair(v, distance[v])); // v = vertex and weight = edge weight between u and v
                    parentDJ[source][v] = u;
                }
            }
        }
    }

private:
    void addDummySource(int dummySource)
    {
        adjList.resize(vertices + 1);
        distance.resize(vertices + 1);
        for (int i = 0; i < vertices; i++)
        {
            addEdge(dummySource, i, 0);
        }
    }

public:
    void johnson(int dummySource)
    {
        addDummySource(dummySource);
        if (!bellman_ford(dummySource))
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

        vector<vector<int>> apsp(vertices, vector<int>(vertices));
        for (int u = 0; u < vertices; u++)
        {
            dijkstra(u);
            apsp[u] = distance;
        }
        printWeightMatrix(apsp);
    }

private:
    void printWeightMatrix(vector<vector<int>> apsp)
    {
        for (int i = 0; i < vertices; i++)
        {
            for (int j = 0; j < vertices; j++)
            {
                if (i == j)
                    continue;
                cout << i << " to " << j << ": ";
                if (apsp[i][j] == INT_MAX)
                    cout << "infinity"
                         << "\n";
                else
                    cout << apsp[i][j] << "\n";
            }
        }
    }

public:
    void printShortestPath(int source, int destination)
    {
        // cout<<source<<" "<<destination<<endl;
        if (source == destination)
        {
            cout << source << " ";
        }
        else if (parentDJ[source][destination] == INT_MIN)
        {
            cout << "No path" << endl;
        }
        else
        {
            printShortestPath(source, parentDJ[source][destination]);
            cout << destination << " ";
        }
    }
};

int main()
{
    int m, n;
    cin >> m >> n;
    // cin >> source >> destination;
    graph g(m, n, true); // starts from 0
    g.defineGraph();
    g.johnson(m); // m = dummy source
    // cout<<"Shortest path by johnson from "<<source<<" to "<<destination<<" : ";
    // g.printShortestPath(source, destination);
    return 0;
}