#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int findWinner(int n,int k)
{
    queue<int> ppl;
    for (int i = 0; i < n; i++)
    {
        int x;
        cin>>x;
        ppl.push(x);
    }
    int count=0;
    while (ppl.size()>1)
    {
        int x = ppl.front();
        ppl.pop();
        count++;
        if(count!=k)
        {
            ppl.push(x);
        }
        else
        {
            count=0;
        }
    }    
    return ppl.front();
}

int main()
{
    freopen("input.in", "r", stdin);
    freopen("output.in", "w", stdout);
    int n, k;
    cin>>n>>k;

    cout<<findWinner(n, k)<<endl;
    
    return 0;
}