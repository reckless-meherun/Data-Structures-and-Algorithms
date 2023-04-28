#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int vertices, edges;

void addEdge(vector<int> adjList[], int u, int v)
{
    if (u < vertices and v < vertices)
    {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }
    else
    {
        cout<<"Graph if full"<<endl;
    }
}

void defineGraph(vector<int> adjList[])
{
    for(int i=0; i<edges; i++)
    {
        int u, v;
        cin>>u>>v;
        //cout<<u<<" "<<v;
        addEdge(adjList, u,v);
    }
}

void printGraph(vector<int> adjList[])
{
	cout<<"v : edges"<<endl;
    for (int i = 0; i < vertices; i++)
    {
        cout<<i<<" : ";
        for(auto v: adjList[i])
            cout<<v<<" ";
        cout<<endl;
    }    
}

int main()
{
    // freopen("input.in", "r", stdin);
    // freopen("output.in", "w", stdout);    
    cin>>vertices>>edges;
    vector<int> adjList[vertices];
    defineGraph(adjList);
    printGraph(adjList);
    
    return 0;
}