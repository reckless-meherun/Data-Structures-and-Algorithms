#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class graph
{
    int vertices;
    int edges;
    bool directed;
    vector<list<pair<int, int>>> adjList;

    int *parent;
    int *distance;
    bool *mst;
    int *key;

public:
    graph(int vertices, int edges, bool ifDirected)
    {
        this->vertices = vertices;
        this->edges = edges;
        adjList.resize(vertices + 1);
        directed = ifDirected;

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

private:
    int findMinVertex()
    {
        int minVertex;
        int minKey = INT_MAX;
        for (int i = 1; i <= vertices; i++)
        {
            if (mst[i] == false and key[i] < minKey)
            {
                minVertex = i;
                minKey = key[i];
                // cout << "minimum key : " << minKey << endl;
            }
        }
        return minVertex;
    }

public:
    void mstPrims()
    {
        int cost = 0;
        mst = new bool[vertices + 1];
        key = new int[vertices + 1];
        // vector<vector<int>> minEdges(vertices+1);
        vector<int> minEdge[edges+1];

        for (int i = 1; i <= vertices; i++)
        {
            key[i] = INT_MAX;
            mst[i] = false;
            // parent[i]=-1;
        }

        // memset(key, 10000, sizeof(key));
        // memset(mst, false, sizeof(mst));
        // memset(parent, -1, sizeof(parent));

        parent[1] = -1;
        key[1] = 1;

        for (int i = 1; i < vertices; i++)
        {
            int u = findMinVertex();

            // cout<<"min ver "<<u<<endl;
            mst[u] = true;
            for (auto v : adjList[u]) // relax
            {
                // minEdges[u] = vector<int>(vertices+1);
                if (mst[v.first] == false and v.second < key[v.first])
                {
                    key[v.first] = v.second;
                    parent[v.first] = u;
                    cost += v.second;
                    minEdge[u][v.first] = v.second;
                }
            }
        }
        // for(int i=1; i<=vertices; i++)
        //     cout<<parent[i]<<" ";

        cout << "Cost : " << cost << endl;
        printMST(minEdge);
    }

private:
    void printMST(vector<int> minEdge[])
    {
        cout << "edges \t weight\n";
        for (int i = 2; i <= vertices; i++)
        {
            cout << parent[i] << " - " << i << " \t "<<minEdge[parent[i]][i]<<"\n";
        }
    }
};

int main()
{
    freopen("input.in", "r", stdin);
    freopen("output.in", "w", stdout);
    graph g(6, 9, false); // starts from 1
    g.defineGraph();
    g.printGraph();
    g.mstPrims();
    return 0;
}