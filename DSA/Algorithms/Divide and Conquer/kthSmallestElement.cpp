#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int hoaresPartition(vector<int> &arr, int low, int high)
{
    int pivot = arr[low];
    int i = low - 1, j = high + 1;

    while (true)
    {
        // Find leftmost element greater than
        // or equal to pivot
        do
        {
            i++;
        } while (arr[i] < pivot);

        // Find rightmost element smaller than
        // or equal to pivot
        do
        {
            j--;
        } while (arr[j] > pivot);

        // If two pointers met.
        if (i >= j)
            return j;

        swap(arr[i], arr[j]);
    }
}

// int lomutosPartition(vector<int> &arr, int low, int high)
// {
//     int pivot_element = arr[high];
//     int j = low;
//     for (int i = low; i <= high - 1; i++)
//     {
//         if (arr[i] <= pivot_element)
//         {
//             swap(arr[j], arr[i]); // not stable because of the swap even after arr[i] being equal to pivot element
//             j++;
//         }
//     }
//     swap(arr[j], arr[high]);
//     int pivot_pos = j;
//     return pivot_pos;
// }

int lomutosPartition(vector<int> &arr, int low, int high)
{
    int pivot = low;
    for (int i = low; i < high; i++)
    {
        if (arr[i] < arr[high])
        {
            swap(arr[pivot], arr[i]); // not stable because of the swap even after arr[i] being equal to pivot element
            pivot++;
        }
    }
    swap(arr[pivot], arr[high]);
    return pivot;
}

int kthSmallestElement(vector<int> &arr, int low, int high, int k)
{
    if (low == high)
        return arr[low];

    int pivot_pos = lomutosPartition(arr, low, high);
    //int i = pivot_pos - low + 1;

    if (pivot_pos == k)
        return arr[pivot_pos];
    else if (k < pivot_pos)
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
    cout << kthSmallestElement(v, 0, n - 1, k-1);
    // for (int i = 0; i < n; i++)
    // {
    //     cout << v[i] << " ";
    // }
    // cout << endl;
    return 0;
}