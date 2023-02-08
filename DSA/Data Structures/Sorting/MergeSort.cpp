#include<bits/stdc++.h>
using namespace std;

void Merge(vector<int> &v, int st, int mid, int ed)
{
    vector<int> temp;

    int i, j;
    i = st;
    j = mid + 1;

    while (i <= mid && j <= ed)
    {
        if (v[i] <= v[j])
        {
            temp.push_back(v[i++]);
        }
        else
        {
            temp.push_back(v[j++]);
        }
    }

    while (i <= mid)
    {
        temp.push_back(v[i++]);
    }

    while (j <= ed)
    {
        temp.push_back(v[j++]);
    }

    for (int i = st; i <= ed; ++i)
        v[i] = temp[i - st];
}

void MergeSort(vector<int> &v, int start, int end)
{
    if (start < end)
    {
        int mid = (start + end) / 2;
        MergeSort(v, start, mid);
        MergeSort(v, mid + 1, end);
        Merge(v, start, mid, end);
    }
}

int main()
{
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> v[i];
    }

    MergeSort(v, 0, n - 1);

    for (int i = 0; i < n; ++i)
    {
        cout << v[i] << " ";
    }
    return 0;
}