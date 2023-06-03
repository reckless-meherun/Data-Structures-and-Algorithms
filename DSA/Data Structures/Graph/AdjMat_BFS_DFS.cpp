#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class Node
{
public:
    int value;
    Node *next;

    Node(int value, Node *next = nullptr)
    {
        this->value = value;
        this->next = next;
    }
};

class Queue
{
private:
    Node *front;
    Node *rear;
    int size;

public:
    Queue()
    {
        this->front = nullptr;
        this->rear = nullptr;
        this->size = 0;
    }

    int get_size()
    {
        return this->size;
    }

    void enqueue(int value)
    {
        Node *newNode = new Node(value);
        if (front == nullptr)
        {
            front = newNode;
            rear = newNode;
            this->size++;
            return;
        }
        rear->next = newNode;
        rear = rear->next;
        this->size++;
    }

    void dequeue()
    {
        if (front == nullptr)
            return;
        Node *temp = front;
        front = front->next;
        this->size--;
        delete temp;
    }
    bool empty()
    {
        return this->size == 0;
    }

    int peek()
    {
        if (front == nullptr)
            return INT_MIN;
        return front->value;
    }

    void print()
    {
        Node *currNode = this->front;

        while (currNode != nullptr)
        {
            cout << currNode->value << " -> ";
            currNode = currNode->next;
        }
        cout << '\n';
    }
};

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
    int **adjMat;
    int *parent;
    COLORS *color;
    int *distance;

public:
    graph(int vertices, int edges, bool ifDirected)
    {
        this->vertices = vertices;
        this->edges = edges;

        /** have to locate memory for the container arrays first, then we can declare some size of array for each array */
        adjMat = new int *[this->vertices + 1];
        for (int i = 1; i <= vertices; i++)
        {
            adjMat[i] = new int[vertices + 1];
        }

        directed = ifDirected;
        color = new COLORS[vertices + 1];
        parent = new int[vertices + 1];
        distance = new int[vertices + 1];
    }

    void defineGraph()
    {
        for (int i = 1; i <= edges; i++)
        {
            int u, v;
            cin >> u >> v;
            addEdge(u, v);
        }
    }

    void addEdge(int u, int v)
    {
        adjMat[u][v] = true;
        if (!directed)
            adjMat[v][u] = true;
    }

    void removeEdge(int u, int v)
    {
        adjMat[u][v] = false;
        adjMat[v][u] = false;
    }

    bool isConnected(int u, int v)
    {
        return adjMat[u][v] or adjMat[v][u];
    }

    int outDegree(int u)
    {
        int outD = 0;
        for (int i = 1; i <= vertices; i++)
        {
            outD += adjMat[u][i];
        }
        return outD;
    }

    int inDegree(int u)
    {
        int inD = 0;
        for (int i = 1; i <= vertices; i++)
        {
            inD += adjMat[i][u];
        }
        return inD;
    }

    void printGraph()
    {
        for (int i = 1; i <= vertices; i++)
        {
            for (int j = 1; j <= vertices; j++)
                cout << adjMat[i][j] << " ";
            cout << endl;
        }
    }

    void BFS(int source)
    {
        memset(color, white, sizeof(color));
        memset(parent, INT_MIN, sizeof(parent));
        memset(distance, INT_MAX, sizeof(distance));

        // queue<int> grey_ver; // vertices that are grey/visited
        Queue grey_ver;

        color[source] = grey;
        distance[source] = 0;
        // grey_ver.push(source);
        grey_ver.enqueue(source);

        while (!grey_ver.empty())
        {
            int u = grey_ver.peek();
            grey_ver.dequeue();

            for (int v = 1; v <= vertices; v++)
            {
                if (adjMat[u][v] != 0 and color[v] == white)
                {
                    color[v] = grey;
                    distance[v] = distance[u] + 1;
                    parent[v] = u;
                    // grey_ver.push(v);
                    grey_ver.enqueue(v);
                }
            }
            color[u] = black;
        }
    }

    void DFS(int source)
    {
        memset(color, white, sizeof(color));
        memset(parent, INT_MIN, sizeof(parent));
        memset(distance, INT_MAX, sizeof(distance));

        DFS_Visit(source);
    }

private:
    void DFS_Visit(int u)
    {
        color[u] = grey;
        for (int v = 1; v <= vertices; v++)
        {
            if (adjMat[u][v] != 0 and color[v] == white)
            {
                color[v] = grey;
                distance[v] = distance[u] + 1;
                parent[v] = u;
                DFS_Visit(v);
            }
        }
        color[u] = black;
    }

public:
    void printShortestPath(int source, int destination)
    {
        cout<<source<<" "<<destination<<endl;
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
    // freopen("input.in", "r", stdin);
    // freopen("output.in", "w", stdout);

/** BFS DFS might act weird in case of directed graph */
    graph g(5, 6, false); // starts from 1
    g.defineGraph();
    g.printGraph();
    cout << g.isConnected(1, 3) << endl;
    cout << g.inDegree(2) << endl;
    cout << g.outDegree(2) << endl;
    g.BFS(3);
    g.printShortestPath(3,4);
    cout<<endl;
    g.DFS(3);
    g.printShortestPath(3,4);
    cout<<endl;
    return 0;
}