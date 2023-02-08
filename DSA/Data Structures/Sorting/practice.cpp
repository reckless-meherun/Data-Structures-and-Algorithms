#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> SortToArrayTwo(vector<int> &v1, int len1, vector<int> &v2, int len2)
{
    vector<int> trans(1000000, -1);
    vector<int> trans_rev(1000000, -1);
    int i;
    for (i = 0; i < len2; i++)
    {
        trans[v2[i]] = i;
        trans_rev[i] = v2[i];
    }
    sort(v1.begin(), v1.end());
    for (int j = 0; j < len1; j++)
    {
        if (trans[v1[j]] == -1)
        {
            v1[j] = trans[v1[j]] = i;
            trans_rev[i] = v1[j];

            // cout << v1[j] << " out" << endl;
            i++;
        }
        else
        {
            v1[j] = trans[v1[j]];
            // cout << v1[j] << endl;
        }
    }
    // for (auto x : v1)
    //     cout << x << " ";
    // auto ans = selection_sort(v1, n, v2, m);
    sort(v1.begin(), v1.end());
    // cout << endl;
    // for (auto x : v1)
    //     cout << x << " ";
    // cout << endl;
    // for (int j = 0; j < len1; j++)
    // {
    //     cout << trans_rev[v1[j]] << " ";
    // }
    // cout << endl;
    return trans_rev;
}

int main()
{
    vector<int> pos(10000000, -1);
    int n, m;
    cin >> n >> m;
    vector<int> a1(n);
    vector<int> a2(m);
    
    for (int i = 0; i < n; i++)
    {
        cin >> a1[i];
    }

    int i;
    for (i = 0; i < m; i++)
    {
        cin >> a2[i];
    }
    auto ans = SortToArrayTwo(a1, n, a2, m);
    for (int j = 0; j < n; j++)
    {
        cout << ans[a1[j]] << " ";
    }
    return 0;
}