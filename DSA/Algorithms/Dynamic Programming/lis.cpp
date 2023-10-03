#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

#define fastio                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);
#define MULTIPLE_TEST \
    int t;            \
    cin >> t;         \
    while (t--)
#define notun '\n'
#define vi vector<int>
#define pb(a) push_back(a)
#define all(x) x.begin(), x.end()
#define forV(x, arr) for (auto x : arr)
#define forP(a, b, arr) for (auto [a, b] : arr)

// local array size = 1e5, global = 1e8
// int = 1e9, long long = 1e18
//  1 sec = 1e7 ~ 1e8



int lis(vector<int> &arr)
{
    int n = arr.size();
    vector<int> dp(n);
    dp[0] = 0;

    vector<int> path(n, -1);

    for (int i = 0; i < n; i++)
    {
        int temp = 0;
        for (int j = 0; j < i; j++)
        {
            if (arr[j] < arr[i])
            {
                if (dp[j] > temp)
                {
                    temp = dp[j];
                    path[i] = j;
                }
                // temp=max(dp[j],temp);
            }
        }
        dp[i] = 1 + temp;
    }
    int temp = path[max_element(all(dp)) - dp.begin()];
    list<int> ans;
    while (temp != -1)
    {
        ans.emplace_front(arr[temp]);
        temp = path[temp];
    }

    forV(x, ans) cout << x << notun;

    return *max_element(all(dp));
}

const int N = 1e7 + 10;
const int mod = 1e9 + 7;

int main()
{

    fastio

        int n;
    cin >> n;

    vector<int> arr(n, 0);

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    cout << lis(arr);

    return 0;
}