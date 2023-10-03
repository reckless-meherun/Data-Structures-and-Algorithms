#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL);
#define MULTIPLE_TEST int t;cin>>t;while(t--)
#define notun '\n'
#define vi vector<int>
#define pb(a) push_back(a)
#define all(x) x.begin(),x.end()
#define forV(x,arr) for(auto x:arr)
#define forP(a,b,arr) for(auto [a,b]: arr)

//local array size = 1e5, global = 1e8
//int = 1e9, long long = 1e18
// 1 sec = 1e7 ~ 1e8

const int N = 1e7+10;


vector<int> price;


vi dp;
int rod_cuttingRec(int n) {
    if(dp[n]!=-1) return dp[n];
    if(n==0) return dp[n]=0;

    int temp = INT_MIN;

    for (int i = 1; i <=n; i++)
    {
        temp = max(price[i]+rod_cuttingRec(n-i),temp);
    }
    return dp[n]=temp;
    
}

int rod_cuttingIter(int n) {
    vector<int> dp(n+1,0);
    dp[0]=0;

    for (int j = 1; j <= n; j++)
    {
        int temp = INT_MIN;

        for (int i = 1; i <= j; i++)
        {
            temp = max(temp,price[i]+dp[j-i]);
        }
        dp[j]=temp;
    }
    return dp[n];
}

int main(){

    fastio

    int n;  cin>>n;
    price.assign(n+1,0);
    dp.assign(n+1,-1);


    for (int i = 1; i <=n; i++)
    {
        cin>>price[i];
    }
    
    cout<<rod_cuttingIter(n);

    

    return 0;
}