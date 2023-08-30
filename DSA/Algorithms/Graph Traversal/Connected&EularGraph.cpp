#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

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
    }

    void defineGraph()
    {
        for (int i = 0; i < edges; i++)
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

    void removeEdge(int u, int v)
    {
        adjList[u].remove(v);
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

    void BFS(int source)
    {
        initialize();

        queue<int> grey_ver; // vertices that are grey/visited
        // Queue grey_ver;

        color[source] = grey;
        distance[source] = 0;
        grey_ver.push(source);
        // grey_ver.enqueue(source);

        while (!grey_ver.empty())
        {
            int u = grey_ver.front();
            // int u = grey_ver.peek();
            grey_ver.pop();
            // grey_ver.dequeue();
            for (auto v : adjList[u])
            {
                if (color[v] == white)
                {
                    color[v] = grey;
                    distance[v] = distance[u] + 1;
                    parent[v] = u;
                    grey_ver.push(v);
                    // grey_ver.enqueue(v);
                }
            }
            color[u] = black; // cause it has been fully explored
        }
    }

    void DFS(int source)
    {
        initialize();
        DFS_Visit(source); // u don't need to run an extra loop, the recursion will visit all the vertices automatically
    }

    void DFS(vector<pair<int, int>> &ordered_node)
    {
        initialize();

        // printGraph();

        for (auto a : ordered_node)
        {
            // if(a.first == 5) cout<<"color of 5 "<<color[a.first]<<endl;
            if (color[a.first] == white)
            {
                // cout<<"white node "<<a.first<<endl;
                DFS_Visit(a.first);
                cout << "\n";
            }
        }
    }

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
        //  cout << "entering Vertex : " << u << " pre V : " << time << endl;
        startingTime[u] = low[u] = time;
        time++;
        int children = 0;
        for (auto v : adjList[u])
        {
            // cout << "Parent : " << u << " Child : " << v << endl;
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

                if (parent[u] == INT_MIN and children > 1) // case 1 : u is a root
                    articulationPoints[u] = true;

                if (parent[u] != INT_MIN and low[v] >= startingTime[u]) // case 2 : at least one component will get separated
                    articulationPoints[u] = true;
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

    void printGraph()
    {
        for (int i = 0; i < vertices; i++)
        {
            cout << i << " : ";
            for (auto v : adjList[i])
            {
                cout << v << " ";
            }
            cout << endl;
        }
    }

    void printStartingTime()
    {
        cout << "\nentering time \n";
        for (int i = 0; i < vertices; i++)
            cout << i << " : " << startingTime[i] << "\n";
    }

    void printFinishingTime()
    {
        cout << "\nleaving time \n";
        for (int i = 0; i < vertices; i++)
            cout << i << " : " << finishingTime[i] << "\n";
    }

    void transpose()
    {
        vector<list<int>> adjList2(vertices + 1);
        if (directed)
        {
            for (int i = 0; i < vertices; i++)
            {
                for (auto v : adjList[i])
                {
                    adjList2[v].push_back(i);
                }
            }
            adjList = adjList2;
        }
    }

private:
    static bool cmp(pair<int, int> &a, pair<int, int> &b) // this is inside graph class that's why u gotta use static here
    {
        return a.second >= b.second;
    }

public:
    vector<pair<int, int>> topologicalSort()
    {
        vector<pair<int, int>> sortedFinishTime;
        for (int i = 0; i < vertices; i++)
        {
            sortedFinishTime.push_back(make_pair(i, finishingTime[i]));
        }
        sort(sortedFinishTime.begin(), sortedFinishTime.end(), cmp);
        cout << endl;
        for (auto v : sortedFinishTime)
        {
            cout << v.first << " " << v.second << "\n";
        }
        return sortedFinishTime;
    }

    void findSCC()
    {
        DFS();
        vector<pair<int, int>> orderedNodes = topologicalSort();
        transpose();
        cout << "\nhmmmm followings are the SCC\n"
             << endl;
        DFS(orderedNodes);
        transpose(); // to back to original form after the work is done
    }

    void printLowValues()
    {
        for (int i = 0; i < vertices; i++)
            cout << i << " : " << low[i] << "\n";
        cout << "\n";
    }

    bool isConnected()
    {
        if (!directed)
        {
            DFS(1);
            for (int i = 0; i < vertices; i++)
            {
                if (color[i] == white and adjList[i].size() > 0) // adjList[i].size() == 0 won't work 'cause if the node is white and it has no child, the graph could be eular because there is no children in that other component
                    return false;
            }
            return true;
        }
        else
        {
            vector<bool> visited1(vertices + 1);
            DFS(1);
            for (int i = 0; i < vertices; i++)
            {
                if (color[i] != white)
                    visited1[i] = true;
            }
            transpose();
            vector<bool> visited2(vertices + 1);
            DFS(1);
            for (int i = 0; i < vertices; i++)
            {
                if (color[i] != white)
                    visited2[i] = true;
            }

            for (int i = 0; i < vertices; i++)
            {
                if (!visited1[i] and !visited2[i])
                {
                    transpose(); //back to the original
                    return false;
                }
            }
            transpose(); //back to the original
            return true;
        }
    }

private:
    int findOddVertex()
    {
        for (int i = 0; i < vertices; i++)
        {
            if (outDegree(i) & 1)
                return i;
        }
        cout<<"no odd vertex\n";
        return -1;
    }

    int findEularPathOrCircuit()
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
                // cout << "indegree " << inDegree(i) << " outdegree " << outDegree(i) << endl;
                if (inDegree(i) - outDegree(i) == 1)
                    positive++;
                else if (outDegree(i) - inDegree(i) == 1)
                    negative++;
                else if (inDegree(i) != outDegree(i))
                    return 0;
                // cout << "going for " << i << endl;
            }

            if (positive == 0 and negative == 0)
                return 2;
            if (positive <= 1 and negative <= 1)
                return 1;
            return 0;
        }
    }

    vector<int> findPath(int source, vector<list<int>> &graphCopy, vector<int> &eularPath)
    {
        while (!graphCopy[source].empty())
        {
            int v = graphCopy[source].back();
            graphCopy[source].pop_back();
            auto it = find(graphCopy[v].begin(), graphCopy[v].end(), source);
            graphCopy[v].erase(it);

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
        vector<list<int>> graphCopy = adjList;
        if (e == 1 or 2) // semi eularian
        {
            int source = 0;
            if (e == 1)
                source = findOddVertex();
            eularPath = findPath(source, graphCopy, eularPath);
            for(auto a: eularPath)
            {
                cout<<a<<" - ";
            }
            cout<<"\n";
        }
        else
        {
            cout << "graph has no eular path or circuit\n";
        }
        return eularPath;
    }

    int isEularian()
    {
        int eular = findEularPathOrCircuit();
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
};

int main()
{
    freopen("input.in", "r", stdin);
    freopen("output.in", "w", stdout);

    graph g(4, 4, false); // starts from 1
    g.defineGraph();
    if (g.isConnected())
        cout << "connected\n";
    else
        cout << "not connected\n";
    g.isEularian();
    g.printEularPath();

    return 0;
}
