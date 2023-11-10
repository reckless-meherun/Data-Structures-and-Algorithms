#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll countInv = 0;
vector<pair<int, int>> indices;

ll Merge(vector<pair<int, int>> &v, int st, int mid, int ed)
{
    vector<pair<int, int>> temp;

    int i, j;
    i = st;
    j = mid + 1;

    while (i <= mid && j <= ed)
    {
        if (v[i].first <= v[j].first)
        {
            temp.push_back(v[i]);
            for (int k = j; k <= ed; k++)
            {
                countInv++;
                indices.push_back({v[i].second, v[k].second});
            }
            i++;
        }
        else
        {
            temp.push_back(v[j++]);
        }
    }

    while (i <= mid)
        temp.push_back(v[i++]);

    while (j <= ed)
        temp.push_back(v[j++]);

    for (int i = st; i <= ed; ++i)
        v[i] = temp[i - st];
    return countInv;
}

ll countInversion(vector<pair<int, int>> &v, int start, int end)
{
    if (start < end)
    {
        int mid = (start + end) / 2;
        countInversion(v, start, mid);   // call one
        countInversion(v, mid + 1, end); // call two
        Merge(v, start, mid, end);       // call merge
    }
    return countInv;
}

void printIndices()
{
    sort(indices.begin(), indices.end());
    cout << endl;
    for (auto a : indices)
    {
        cout << a.first << " " << a.second << endl;
    }
}

int main()
{
    int n;
    cin >> n;
    vector<pair<int, int>> v(n);
    for (int i = 0; i < n; ++i)
    {
        int x;
        cin >> x;
        v[i].first = x;
        v[i].second = i;
    }
    cout << countInversion(v, 0, n - 1);
    printIndices();
    return 0;
}