#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int parent[10000];
int Size[10000];

void make(int v)
{
    parent[v] = v;
    Size[v] = 1;
}

int find(int v)
{
    if (v == parent[v])
        return v;
    /** path compression */
    return parent[v] = find(parent[v]);
}

void Union(int a, int b)
{
    a = find(a);
    b = find(b);
    if (a == b)
        return;
    /** Union by size of trees */
    if (Size[a] < Size[b])
        swap(a, b);
    parent[b] = a;
    Size[a] += Size[b];
}

int main()
{
    freopen("input.in", "r", stdin);
    freopen("output.in", "w", stdout);
    int n, k;
    cin>>n>>k;
    for (int i = 1; i <=n; i++)
    {
        make(i);
    }
    while(k--)
    {
        int u,v;
        cin>>u>>v;
        Union(u,v);
    }

    int conct_count=0;
    for (int i = 1; i <=n ; i++)
    {
        if(i == find(i))
            conct_count++;
    }
    
    cout<<conct_count<<endl;

    return 0;
}