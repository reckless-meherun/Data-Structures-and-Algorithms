#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int parent[10000];

int make(int v)
{
    parent[v] = v;
}

int find(int v)
{
    if (v == parent[v])
        return v;
    return find(parent[v]);
}

void Union(int a, int b)
{
    a = find(a);
    b = find(b);
    if (a == b)
        return;
    parent[b] = a;
}

int main()
{
    freopen("input.in", "r", stdin);
    freopen("output.in", "w", stdout);
    
    return 0;
}