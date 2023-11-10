#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

#define fastio                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);
#define MULTIPLE_TEST \
    int t;            \
    cin >> t;         \
    while (t--)
#define notun '\n'
#define vi vector<int>
#define pb(a) push_back(a)
#define all(x) x.begin(), x.end()
#define forV(x, arr) for (auto x : arr)
#define forP(a, b, arr) for (auto [a, b] : arr)

// local array size = 1e5, global = 1e8
// int = 1e9, long long = 1e18
//  1 sec = 1e7 ~ 1e8

const int N = 1e7 + 10;
const int mod = 1e9 + 7;

class Edge
{
public:
    int to, flow, capacity;

    Edge(int to, int capacity)
    {
        this->to = to;
        this->capacity = capacity;
        this->flow = 0;
    }
};

vector<vector<Edge>> adj;
vector<int> parent;

void addEdge(int from, int to, int capacity)
{
    adj[from].push_back(Edge(to, capacity));
    adj[to].push_back(Edge(from, 0));
}

int bfs(int source, int sink)
{
    fill(all(parent), -1);
    parent[source] = -2;

    queue<pair<int, int>> q;
    q.push({source, INT_MAX});

    while (!q.empty())
    {
        auto [vertex, flow] = q.front();
        q.pop();

        for (Edge &edge : adj[vertex])
        {
            if (parent[edge.to] != -1 || edge.capacity <= edge.flow)
                continue;

            parent[edge.to] = vertex;

            int min_capacity = min(flow, edge.capacity - edge.flow);

            if (edge.to == sink)
                return min_capacity;

            q.push({edge.to, min_capacity});
        }
    }
    return 0;
}

int edmond_karp(int source, int sink)
{
    int maxFlow = 0;
    int min_capacity;

    while (min_capacity = bfs(source, sink))
    {
        maxFlow += min_capacity;
        int curr = sink;

        while (curr != source)
        {
            int prev = parent[curr];
            for (Edge &edge : adj[prev])
            {
                if (edge.to == curr)
                {
                    edge.flow += min_capacity;
                    break;
                }
            }
            for (Edge &edge : adj[curr])
            {
                if (edge.to == prev)
                {
                    edge.flow -= min_capacity;
                    break;
                }
            }
            curr = prev;
        }
    }
    return maxFlow;
}
// for person a doing multiple tasks(n) set capacity of (s,a)=n
// for task b done by multiple persons(n) set capacity of (b,t)=n
// for person a doing task b multiple times(n) set capacity of (a,b)=n
// sum of flow from source gives total count of tasks done
// sum of flow in sink gives, total count of person

int main()
{

    fastio int len_a, len_b;
    cin >> len_a >> len_b;

    int source = 0;
    int sink = len_a + len_b + 1;

    int size = len_a + len_b + 2;

    adj.assign(size, vector<Edge>());
    parent.assign(size, -1);

    for (int i = 1; i <= len_a; i++)
    {
        addEdge(source, i, 1);
    }

    int len_connections;
    cin >> len_connections;

    for (int j = 0; j < len_connections; j++)
    {
        int person, task;
        cin >> person >> task;

        addEdge(person, len_a + task, 1);
    }

    for (int j = len_a + 1; j <= len_a + len_b; j++)
    {
        addEdge(j, sink, 1);
    }
    int i = 0;

    int maxMatch = edmond_karp(source, sink);

    cout << maxMatch << notun;

    return 0;
}