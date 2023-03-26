#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int BinSearch(vector<int> &v, int st, int ed)
{
    int mid;
    int ans = v[st];
    while (st <= ed)
    {
        mid = st + (ed - st) / 2;
        if (v[st] < v[ed])
        {
            return v[st]; // the array is not rotated anymore
        }
        if (v[mid] > v[st])
        {
            st = mid + 1;
        }
        else
        {
            if (v[mid] < ans)
                ans = v[mid];
            ed = mid - 1;
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
    cout << BinSearch(v, 0, n - 1) << endl;
    return 0;
}