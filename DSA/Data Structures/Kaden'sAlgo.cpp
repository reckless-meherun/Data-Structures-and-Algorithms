#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll maximum_subarray_sum(ll arr[], ll len)
{
    ll max_curr_sum=0;
    ll max_sum_soFar=INT_MIN;

    for (ll i = 0; i < len; i++)
    {
        max_curr_sum += arr[i];
    
        if(max_curr_sum>max_sum_soFar)
            max_sum_soFar = max_curr_sum;
        if(max_curr_sum<0)
            max_curr_sum = 0; //as the more less negative, the bigger the sum is
    }
    return max_sum_soFar;   
}

int main()
{
    ll arr[2000000];
    ll n;
    cin>>n;
    for (ll i = 0; i < n; i++)
    {
        cin>>arr[i];
    }
    cout<<maximum_subarray_sum(arr, n)<<endl;     
    return 0;
}