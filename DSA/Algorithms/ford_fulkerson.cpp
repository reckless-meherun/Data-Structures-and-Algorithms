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
vector<bool> visited;

void addEdge(int from,int to, int capacity) {
    adj[from].push_back(Edge(to,capacity));
    adj[to].push_back(Edge(from,0));
}

int dfs(int vertex,int minCapacity,int sink) {
    if(vertex==sink) return minCapacity;
    visited[vertex]=true;

    for(Edge& edge: adj[vertex]) {
        if(visited[edge.to] || edge.capacity<=edge.flow) continue;

        int newMinCapacity = min(minCapacity,edge.capacity-edge.flow);
        int residualCapacity = dfs(edge.to,newMinCapacity,sink);

        if(residualCapacity>0) {
            edge.flow+=residualCapacity;

            for(Edge& backEdge: adj[edge.to]) {
                if(backEdge.to==vertex) {
                    backEdge.flow-=residualCapacity;
                    break;
                }
            }
            return residualCapacity;
        }
    }
    return 0;

}

int ford_fulkerson(int source, int sink) {
    int max_flow=0;
    while(true) {
        visited.assign(adj.size(),false);

        int residualCapaciity = dfs(source,INT_MAX,sink);

        if(residualCapaciity==0) break;

        max_flow+=residualCapaciity;
    }
    return max_flow;
}




int main(){

    fastio

    int V,E;    cin>>V>>E;
    adj.assign(V,vector<Edge>());
    visited.assign(V,false);

    for (int i = 0; i < E; i++)
    {
        int from, to,capacity;

        cin>>from>>to>>capacity;

        addEdge(from,to,capacity);
    }

    int source, sink;
    cin>>source>>sink;
    int maxFlow = ford_fulkerson(source,sink);
    cout<<maxFlow<<notun;


    return 0;
}