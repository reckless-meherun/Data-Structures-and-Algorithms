#include<bits/stdc++.h>
using namespace std;

int main()
{
    long long n, q;
    cin>>n>>q;
    vector<long long> v(n+1,0);
    vector <long long> sum(n+1,0);
    long long i=1;
    sum[0] = v[0] = 0;
    for(;i<=n;i++)
    {
        cin>>v[i];
            sum[i] += v[i] + sum[i-1];
    }
    for (long long i = 1; i <= q; i++)
    {
        long long a, b;
        cin>>a>>b;
        cout<<sum[b]-sum[a-1]<<endl;
    }    
    return 0;
}