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

void quickSort(vector<int> &arr, int low, int high)
{
    if (low < high)
    {
        int pivot_pos = partition(arr, low, high);
        quickSort(arr, low, pivot_pos - 1);
        quickSort(arr, pivot_pos + 1, high);
    }
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
    quickSort(v, 0, n - 1);
    for (int i = 0; i < n; i++)
    {
        cout << v[i] << " ";
    }
    cout << endl;
    return 0;
}