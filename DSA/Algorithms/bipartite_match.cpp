#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define vertex_traverse(x) x.begin(), x.end()

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
    fill(vertex_traverse(parent), -1);
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

int main()
{
    int len_a, len_b;
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

    cout << maxMatch << "\n";
    return 0;
}