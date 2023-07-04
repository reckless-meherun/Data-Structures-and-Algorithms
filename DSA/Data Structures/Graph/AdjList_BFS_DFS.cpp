#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class Node{
public:
    int value;
    Node* next;

    Node(int value, Node* next=nullptr){
        this->value=value;
        this->next = next;
    }
};


class Queue{
private:
    Node* front;
    Node* rear;
    int size;

public:

    Queue(){
        this->front = nullptr;
        this->rear = nullptr;
        this->size=0;
    }

    int get_size(){
        return this->size;
    }

    void enqueue(int value){
        Node* newNode = new Node(value);
        if(front==nullptr){
            front=newNode;
            rear = newNode;
            this->size++;
            return;
        }
        rear->next = newNode;
        rear = rear->next;
        this->size++;
    }

    void dequeue(){
        if(front==nullptr) return;
        Node* temp = front;
        front = front->next;
        this->size--;
        delete temp;
    }
    bool empty(){
        return this->size==0;
    }

    int peek(){
        if(front==nullptr) return INT_MIN;
        return front->value;
    }

    void print(){
        Node* currNode = this->front;

        while(currNode!=nullptr){
            cout<<currNode->value<<" -> ";
            currNode = currNode->next;
        }cout<<'\n';
        
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
    vector<list<int>> adjList;
    COLORS *color;
    int *parent;
    int *distance;

public:
    graph(int vertices, int edges, bool ifDirected)
    {
        this->vertices = vertices;
        this->edges = edges;
        adjList.resize(vertices+1);
        directed = ifDirected;
        color = new COLORS[vertices+1];
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
            cout<<u<<" "<<v<<endl;
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

    void BFS(int source)
    {
        // initialize loop
        for (int i = 1; i <= vertices; i++)
        {
            for (auto v : adjList[i])
            {
                color[v] = white;
                parent[v] = INT_MIN;
                distance[v] = INT_MAX;
            }
        }

        //queue<int> grey_ver; // vertices that are grey/visited
        Queue grey_ver;

        color[source] = grey;
        distance[source] = 0;
        //grey_ver.push(source);
        grey_ver.enqueue(source);

        while (!grey_ver.empty())
        {
            // int u = grey_ver.front();
            int u = grey_ver.peek();
            // grey_ver.pop();
            grey_ver.dequeue();
            for (auto v : adjList[u])
            {
                if (color[v] == white)
                {
                    color[v] = grey;
                    distance[v] = distance[u] + 1;
                    parent[v] = u;
                    //grey_ver.push(v);
                    grey_ver.enqueue(v);
                }
            }
            color[u] = black; // cause it has been fully explored
        }
    }

    void DFS(int source)
    {
        // initialize loop
        for (int i = 1; i <= vertices; i++)
        {
            for (auto v : adjList[i])
            {
                color[v] = white;
                parent[v] = INT_MIN;
                distance[v] = INT_MAX;
            }
        }
        
        DFS_Visit(source); // u don't need to run an extra loop, the recursion will visit all the vertices automatically
    }
    
private:
    void DFS_Visit(int u)
    {
        /** Action on a vertex (u) after entering the vertex */
        color[u] = grey;
        cout<<"Vertex : "<<u<<endl;
        for (auto v : adjList[u])
        {
            //cout<<"Parent : "<<u<<" Child : "<<v<<endl;
            /** Action on ANY child (v) of vertex (u) before entering the child */
            if (color[v] == white)
            {
                /** Action on an unvisited/white child (v) of vertex (u) before entering the child */
                color[v] = grey;
                distance[v] = distance[u] + 1;
                parent[v] = u;
                DFS_Visit(v);
                /** Action on the visited child (v) of vertex (u) after leaving the child */
            }
            /** Action on ANY VISITED child (v) of vertex (u) after leaving the child */
        }
        /** Action on a vertex (u) before leaving the vertex */
        color[u] = black;
    }

public:
    void printShortestPath(int source, int destination)
    {
        //cout<<source<<" "<<destination<<endl;
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
        for (int i = 1; i <= vertices; i++)
        {
            cout << i << " : ";
            for (auto v : adjList[i])
            {
                cout << v << " ";
            }
            cout << endl;
        }
    }
};

int main()
{
    freopen("input.in", "r", stdin);
    freopen("output.in", "w", stdout);
    
    /** BFS DFS might act weird in case of directed graph */

    graph g(5, 6, false); //starts from 1
    g.defineGraph();
    g.printGraph();
    g.BFS(3);	
	cout<<"Shortest path : ";
    /** u have to use the same source here, the one u chose to do BFS with; different source won't work, why? simulate and think */
    g.printShortestPath(3, 4);
    cout<<endl;
    /** u cannot use DFS in between BFS and printing any shortest path because that changes the graph totally */
    g.DFS(3);
    g.printShortestPath(3, 4);
    
    return 0;
}