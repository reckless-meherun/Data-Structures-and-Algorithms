#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e7 + 10, mod = 1e9 + 7;

class DisjointSet
{
private:
    int n;
    int *parent;
    int *rank;

public:
    DisjointSet(int n);
    void make(int i);
    void makeSet();
    int find(int i);
    void Union(int a, int b);
};

DisjointSet::DisjointSet(int n)
{
    parent = new int[n];
    memset(parent, -1, sizeof parent);
    rank = new int[n];
    memset(rank, -1, sizeof rank);
    this->n = n;

    makeSet();
}

void DisjointSet::make(int a)
{
    parent[a] = a;
    rank[a] = 1;
}

void DisjointSet::makeSet()
{
    for (int i = 0; i < n; i++)
    {
        parent[i] = i;
        rank[i] = 1;
    }
}

int DisjointSet::find(int i)
{
    if (parent[i] == i)
        return i;

    return parent[i] = find(parent[i]); // path compression
}

void DisjointSet::Union(int a, int b)
{
    a = find(a);
    b = find(b);

    if (a == b)
        return;

    if (rank[a] < rank[b])
    {
        parent[a] = b;
    }
    else if (rank[b] < rank[a])
    {
        parent[b] = a;
    }
    else
    {
        parent[b] = a;
        rank[a]++;
    }
}

bool hasCycle(vector<int> adj[], int n)
{
    DisjointSet *d = new DisjointSet(n);

    for (int i = 0; i < n; i++)
    {
        for (int j : adj[i])
        {
            int rootI = d->find(i);
            int rootJ = d->find(j);

            if (rootI == rootJ)
                return true;
            else
                d->Union(i, j);
        }
    }
    return false;
}

int main()
{

    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    int n, m;
    cin >> n >> m;
    DisjointSet *d = new DisjointSet(n);

    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        d->Union(a, b);
    }

    // d->Union(0,2);
    // d->Union(4,2);
    // d->Union(3,1);

    if (d->find(4) == d->find(0))
        cout << "Yes\n";
    else
        cout << "No\n";
    if (d->find(1) == d->find(0))
        cout << "Yes\n";
    else
        cout << "No\n";
    return 0;
}