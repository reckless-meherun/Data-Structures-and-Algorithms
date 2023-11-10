#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL);
#define MULTIPLE_TEST int t;cin>>t;while(t--)
#define notun '\n'
#define vi vector<int>
#define pb(a) push_back(a)
#define all(x) x.begin(),x.end()
#define forV(x,arr) for(auto x:arr)
#define forP(a,b,arr) for(auto [a,b]: arr)

//local array size = 1e5, global = 1e8
//int = 1e9, long long = 1e18
// 1 sec = 1e7 ~ 1e8

const int N = 1e7+10;
const int mod = 1e9+7;

class Edge {
public:
    int to;
    int flow;
    int capacity;

    Edge(int to, int capacity) {
        this->to = to;
        this->capacity = capacity;
        this->flow =0;
    }
};

vector<vector<Edge>> adj;
vector<int> parent;

void addEdge(int from,int to, int capacity) {
    adj[from].push_back(Edge(to,capacity));
    adj[to].push_back(Edge(from,0));
}

int bfs(int vertex,int sink) {
    fill(all(parent),-1);
    
    parent[vertex]=-2;
    queue<pair<int,int>> q;
    q.push({vertex,INT_MAX});

    while(!q.empty()) {
        auto [vertex,flow] = q.front();
        q.pop();

        for(Edge& edge: adj[vertex]) {
            if(parent[edge.to]!=-1 || edge.capacity<=edge.flow) continue;
            
            parent[edge.to]=vertex;
            int min_capacity = min(flow,edge.capacity-edge.flow);

            if(edge.to==sink) return min_capacity;

            q.push({edge.to,min_capacity}); 

        }
    }
    return 0;

}

int edmond_karp(int source, int sink) {
    int maxFlow=0;

    int min_capacity;

    while(min_capacity=bfs(source,sink)) {
        maxFlow+=min_capacity;

        int curr = sink;

        while(curr!=source) {
            int prev = parent[curr];

            for(Edge& edge: adj[prev]) {
                if(edge.to==curr) {
                    edge.flow+=min_capacity;
                    break;
                }
            }
            for(Edge& edge: adj[curr]) {
                if(edge.to==prev) {
                    edge.flow-=min_capacity;
                    break;
                }
            }
            curr = prev;
        }
    }
    return maxFlow;
}

int main(){

    fastio

    int V,E;    cin>>V>>E;
    adj.assign(V,vector<Edge>());
    parent.assign(V,-1);

    for (int i = 0; i < E; i++)
    {
        int from, to,capacity;

        cin>>from>>to>>capacity;

        addEdge(from,to,capacity);
    }

    int source, sink;
    cin>>source>>sink;
    int maxFlow = edmond_karp(source,sink);
    cout<<maxFlow<<notun;


    return 0;
}