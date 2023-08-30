/** weighted graph cannot be used */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

typedef pair<int, int> iPair;
#define MAX_VALUE 1e9 + 7;

enum COLORS
{
    white = 0,
    grey = 1,
    black = 2
};

class graph
{
    int vertices;
    int edges;
    vector<vector<int>> adjList;
    vector<COLORS> color;
    vector<int> parent;
    vector<int> distance;
    vector<int> topoOrder;
    bool directed;
    bool weighted;
    bool hasCycle = false;
    vector<int> startTime;
    vector<int> endTime;
    vector<vector<int>> scc;
    vector<int> low;
    int totalSCC = 0;
    int time = 1;
    vector<bool> articulationPoint;

public:
    graph(int vertices, int edges, bool directed, bool weighted)
    {
        this->vertices = vertices;
        this->edges = edges;
        this->directed = directed;
        this->weighted = weighted;
        adjList.resize(vertices);
        parent.resize(vertices);
        distance.resize(vertices);
        color.resize(vertices);
        topoOrder.reserve(vertices);
        startTime.resize(vertices);
        endTime.resize(vertices);
        low.resize(vertices);
        articulationPoint.resize(vertices);
        defineGraph();
    }

private:
    void defineGraph()
    {
        int u, v;
        for (int i = 0; i < edges; i++)
        {
            cin >> u >> v;
            addEdge(u, v);
        }
    }

    void addEdge(int u, int v)
    {
        adjList[u].push_back(v);
        if (!directed)
        {
            adjList[v].push_back(u);
        }
    }

public:
    void removeEdge(int u, int v)
    {
        auto it1 = find(adjList[u].begin(), adjList[u].end(), v);
        auto it2 = find(adjList[v].begin(), adjList[v].end(), u);
        if (it1 != adjList[u].end())
            adjList[u].erase(it1);
        if (it2 != adjList[v].end())
            adjList[v].erase(it2);
    }

public:
    void printGraph()
    {
        if (!weighted)
        {
            for (int i = 0; i < vertices; i++)
            {
                cout << i << " : ";
                for (auto u : adjList[i])
                {
                    cout << u << " ";
                }
                cout << "\n";
            }
        }
        else
        {
            for (int i = 0; i < vertices; i++)
            {
                cout << i << " : ";
                for (auto u : adjList[i])
                {
                    cout << u << " ";
                }
                cout << "\n";
            }
        }
    }

private:
    void initialize(int source)
    {
        time = 1;
        for (int i = 0; i < vertices; i++)
        {
            color[i] = white;
            parent[i] = -1;
            distance[i] = MAX_VALUE;
            startTime[i] = 0;
            endTime[i] = 0;
            low[i]=MAX_VALUE;
        }
        distance[source] = 0;
    }

    void DFS(int source)
    {
        initialize(source);
        DFS_Visit(source);
    }

    void DFS()
    {
        initialize(0);
        for (int i = 0; i < vertices; i++)
        {
            if (color[i] == white)
            {
                DFS_Visit(i);
            }
        }
    }

    void DFS(vector<int> orderedNodes)
    {
        initialize(orderedNodes[0]);
        for (auto u : orderedNodes)
        {
            if (color[u] == white)
            {
                DFS_Visit(u);
                totalSCC++;
                cout << "\n";
            }
        }
    }

    void DFS_Visit(int u)
    {
        color[u] = grey;
        startTime[u] = time;
        time++;
        int child = 0;
        cout << u << " entering at time " << startTime[u] << endl;
        for (auto v : adjList[u])
        {
            if (color[v] == grey)
                hasCycle = true;
            if (color[v] == white)
            {
                child++;
                color[v] = grey;
                parent[v] = u;
                distance[v] = distance[u] + 1;
                DFS_Visit(v);
                low[u] = min(low[v], low[u]);

                if (parent[u] == -1 and child > 1)
                    articulationPoint[u] = true;
                if (parent[u] != -1 and low[v] >= startTime[u])
                    articulationPoint[u] = true;
            }
            else if (v != parent[u])
            {
                low[u] = min(low[u], startTime[v]);
            }
        }
        color[u] = black;
        endTime[u] = time;
        time++;
        cout << u << " leaving at time " << endTime[u] << endl;
        topoOrder.push_back(u);
    }

public:
    vector<int> topologicalSort()
    {
        DFS();
        reverse(topoOrder.begin(), topoOrder.end());
        if (hasCycle)
            cout << "The sort is not topological\n";

        for (auto a : topoOrder)
            cout << a << " ";
        cout << "\n";
        return topoOrder;
    }

    void transpose()
    {
        vector<vector<int>> adjList2(vertices);
        if (!directed)
            return;

        for (int i = 0; i < vertices; i++)
        {
            for (auto v : adjList[i])
            {
                adjList2[v].push_back({i});
            }
        }
        adjList = adjList2;
    }

    void findSCC()
    {
        auto orderedNodes = topologicalSort();
        // printGraph();
        // cout<<endl;
        transpose();
        // printGraph();
        cout << "SCC:\n";
        DFS(orderedNodes);
        cout << "total SCC " << totalSCC << endl;
        transpose();
    }

    bool isConnected()
    {
        if (!directed)
        {
            DFS(0);
            for (int i = 0; i < vertices; i++)
                if (color[i] == white and adjList[i].size() > 0)
                    return false;
            return true;
        }
        else
        {
            vector<bool> visited1(vertices);
            DFS(0);

            for (int i = 0; i < vertices; i++)
            {
                if (color[i] != white)
                    visited1[i] = true;
            }

            transpose();

            vector<bool> visited2(vertices);
            DFS(0);

            for (int i = 0; i < vertices; i++)
            {
                if (color[i] != white)
                    visited2[i] = true;
            }

            transpose(); // back to the original

            for (int i = 0; i < vertices; i++)
            {
                if (!visited1[i] and !visited2[i])
                    return false;
            }
            return true;
        }
    }

    int outDegree(int u)
    {
        return adjList[u].size();
    }

    int inDegree(int u)
    {
        if (!directed)
            return outDegree(u);

        int inD = 0;
        for (int i = 0; i < vertices; i++)
        {
            for (auto v : adjList[i]) /** inDegree : how many times u is in the lists of each vertex list */
            {
                if (v == u)
                    inD++;
            }
        }

        return inD;

        /** can be done with binary search as well */
        /** inD = 0;
        for (int i = 0; i < vertices; i++)
        {
            sort(adjList[i].begin(), adjList[i].end());
            if(binary_search(adjList[i].begin(), adjList[i].end(), u))
                inD++;
        }
        return inD; */
    }

    int countEulerNumber()
    {
        if (!isConnected())
            return 0;
        int oddVertex = 0, positive = 0, negative = 0;

        if (!directed)
        {
            for (int i = 0; i < vertices; i++)
            {
                if (outDegree(i) & 1)
                    oddVertex++;
            }
            return (oddVertex > 2) ? 0 : ((oddVertex == 0) ? 2 : 1); // if semi-eularian, return 1; if eularian, return 2}
        }
        else
        {
            for (int i = 0; i < vertices; i++)
            {
                if (inDegree(i) - outDegree(i) == 1)
                    positive++;
                else if (outDegree(i) - inDegree(i) == 1)
                    negative++;
                else if (inDegree(i) != outDegree(i))
                    return 0;
            }

            if (positive == 0 and negative == 0)
                return 2;
            if (positive <= 1 and negative <= 1)
                return 1;
            return 0;
        }
    }

    int isEularian()
    {
        int eular = countEulerNumber();
        if (eular == 0)
        {
            cout << "not eularian\n";
            return 0;
        }
        if (eular == 1)
        {
            cout << "semi eularian\n";
            return 1;
        }
        if (eular == 2)
        {
            cout << "eularian\n";
            return 2;
        }
        return -1;
    }

private:
    int findOddVertex()
    {
        for (int i = 0; i < vertices; i++)
        {
            if (outDegree(i) & 1)
                return i;
        }
        cout << "no odd vertex\n";
        return -1;
    }

    vector<int> findPath(int source, vector<vector<int>> &graphCopy, vector<int> &eularPath)
    {
        cout << source << endl;
        while (!graphCopy[source].empty())
        {
            int v = graphCopy[source].back();
            graphCopy[source].pop_back();

            if (!directed)
            {
                auto it = find(graphCopy[v].begin(), graphCopy[v].end(), source);
                graphCopy[v].erase(it);
            }

            findPath(v, graphCopy, eularPath);
        }
        eularPath.push_back(source);
        return eularPath;
    }

public:
    vector<int> printEularPath()
    {
        int e = isEularian();
        vector<int> eularPath;
        vector<vector<int>> graphCopy = adjList;
        if (e == 1 or 2) // semi eularian
        {
            int source = 0;
            if (e == 1)
                source = findOddVertex();
            eularPath = findPath(source, graphCopy, eularPath);
            for (auto a : eularPath)
            {
                cout << a << " - ";
            }
            cout << "\n";
        }
        else
        {
            cout << "graph has no eular path or circuit\n";
        }
        return eularPath;
    }

    vector<bool> findArticulationPoints()
    {
        DFS();
        for (int i = 0; i < vertices; i++)
            if (articulationPoint[i])
                cout << i << " ";
        cout << "\n";
        return articulationPoint;
    }
};

int main()
{
    int m, n;
    cin >> m >> n;
    graph g(m, n, true, false);
    g.printGraph();
    g.findArticulationPoints();

    return 0;
}