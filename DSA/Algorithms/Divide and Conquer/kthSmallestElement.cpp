#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int partition(vector<int> &arr, int low, int high)
{
    int pivot_element = arr[high];
    int j = low;
    for (int i = low; i <= high - 1; i++)
    {
        if (arr[i] <= pivot_element)
        {
            swap(arr[j], arr[i]); // not stable because of the swap even after arr[i] being equal to pivot element
            j++;
        }
    }
    swap(arr[j], arr[high]);
    int pivot_pos = j;
    return pivot_pos;
}

int kthSmallestElement(vector<int> &arr, int low, int high, int k)
{
    if (low == high)
        return arr[low];

    int pivot_pos = partition(arr, low, high);
    int i = pivot_pos-low+1;
    
    if (i == k)
        return arr[pivot_pos];
    else if (i > k)
        return kthSmallestElement(arr, low, pivot_pos - 1, k);
    else
        kthSmallestElement(arr, pivot_pos + 1, high, k);
}

int main()
{
    int n, k;
    cin >> n >> k;
    vector<int> v(n);
    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
    }
    cout << kthSmallestElement(v, 0, n - 1, k);
    // for (int i = 0; i < n; i++)
    // {
    //     cout << v[i] << " ";
    // }
    // cout << endl;
    return 0;
}