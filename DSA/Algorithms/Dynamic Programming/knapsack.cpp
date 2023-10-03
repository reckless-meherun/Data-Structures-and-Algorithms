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
const int mod = 1e9+7;

vector<int> price;
vector<int> weight;

int knapsack(int n,int W) {
    
    vector<vector<int>> sack(n+1, vector<int>(W+1,0));

    for (int i = 1; i <= n; i++)
    {   
        for (int j = 1; j <= W; j++)
        {
            if(j>=weight[i-1]) {
                sack[i][j]= max(sack[i-1][j],price[i-1]+sack[i-1][j-weight[i-1]]);

            }
        }
        
    }
    
    return sack[n][W];

}

int main(){

    fastio

    int n,W;    cin>>n>>W;
    price.assign(n,0);
    weight.assign(n,0);

    for (int i = 0; i < n; i++)
    {
        cin>>weight[i];
    }
    for (int i = 0; i < n; i++)
    {
        cin>>price[i];
    }
    cout<<knapsack(n,W);

    

    return 0;
}