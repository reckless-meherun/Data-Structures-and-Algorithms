#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class dsu
{
    int *parent, *rank, size;

public:
    dsu(int size)
    {
        this->size = size;
        parent = new int[size];
        rank = new int[size];
        memset(parent, -1, sizeof(parent));
        memset(rank, -1, sizeof(rank));
        makeSet();
    }
    void makeSet()
    {
        for (int v = 0; v < size; v++)
        {
            parent[v] = v;
            rank[v] = 1;
        }
    }
    void make(int a)
    {
        parent[a]=a;
        rank[a]=1;
    }
    int findRoot(int v)
    {
        if (v == parent[v])
            return v;
        return parent[v] = findRoot(parent[v]); /** the return value is the same for both optimized and unoptimized version; but here we are just resetting the parent of every node to root on the way back home recursion so that it takes much less time for the next findRoot that will be called */
    }
    void Union(int a, int b)
    {
        a = findRoot(a);
        b = findRoot(b);
        //cout<<a<<" "<<b<<endl;
        if (a == b)
            return;
        if(rank[a]<rank[b])
        {
            parent[a] = b;
        }
        else if(rank[a]>rank[b])
        {
            parent[b] = a;
        }
        else
        {
            parent[b] = a;
            rank[a]++;
        }
        //cout<<a<<" "<<b<<endl;
    }
};

int main()
{
    // freopen("input.in", "r", stdin);
    // freopen("output.in", "w", stdout);
    dsu d(4);
    d.Union(2,3);
    d.Union(1,0);
     cout<<d.findRoot(0);
    cout<<d.findRoot(2);
    cout<<d.findRoot(3);
    cout<<d.findRoot(1);

    return 0;
}