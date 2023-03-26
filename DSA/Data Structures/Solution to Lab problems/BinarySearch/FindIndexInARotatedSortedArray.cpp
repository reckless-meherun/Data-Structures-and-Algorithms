#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int BinSearch(vector<int> &v, int st, int ed, int find)
{
    int mid;
    int ans = -1;

    while (st <= ed)
    {
        mid = st + (ed - st) / 2;
        
        if (v[mid] == find)
        {
            return mid;
        }

        if (v[mid] > v[st]) // left subarray is sorted
        {
            if (find >= v[st] and find <= v[mid]) // write condition for the sorted subarray
            {
                ans = mid;
                ed = mid - 1;
            }
            else
                st = mid + 1;
        }
        else // right subarray is sorted
        {
            if(find>=v[mid] and find <= v[ed]) // write condition for the sorted subarray
            {
                ans = mid;
                st = mid+1;
            }
            else
                ed = mid-1;
        }
    }
    return ans;
}

int main()
{
    freopen("input.in", "r", stdin);
    freopen("output.in", "w", stdout);
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
    }
    int x;
    cin>>x;
    cout<<BinSearch(v, 0, n-1, x);
    return 0;
}