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

int lower_bound(vector<int>& arr, int val) {
    int low = 0, high = arr.size()-1;

    while(low<high) {
        int mid = (low+high)>>1;
        if(val<=arr[mid]) high= mid;
        else low=mid+1;

    }
    return low;
}

//not right order, just length
int lis_greedy(vector<int>& arr) {
    vector<int> ans;
    int n= arr.size();

    ans.push_back(arr[0]);

    for (int i = 1; i < n; i++)
    {
        if(arr[i]>ans.back()) {
            ans.push_back(arr[i]);
        }
         else {
            int indx= lower_bound(ans,arr[i]);
            ans[indx]=arr[i];
        }
    }

    return ans.size();
    
}

int main(){

    fastio
    
    int n;  cin>>n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        cin>>arr[i];
    }
    // vi a{9};
    // cout<<lower_bound(a,2)<<notun;

    cout<<lis_greedy(arr);
    
    

    return 0;
}