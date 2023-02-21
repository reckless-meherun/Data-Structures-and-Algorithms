#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int Count = 0;

int remove(vector<int> &v)
{
    if(v.size()==1)
        return v[0];
    
    if(Count&1)
    {
        
    }
    else
    {

    }
}

int lastRemaining(int n)
{
    vector<int> v;
    for (int i = 0; i < n; i++)
    {
        int x;
        cin>>x;
        v.push_back(x);
    }
    remove(v);
}

int main()
{
    freopen("input.in", "r", stdin);
    freopen("output.in", "w", stdout);

    return 0;
}