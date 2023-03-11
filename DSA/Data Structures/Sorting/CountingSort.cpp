#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int const range = 100000;

void CountingSort(int arr[], int len)
{
    int count[100000];
    memset(count, 0, sizeof(count));
    for (int i = 0; i < len; i++)
    {
        count[arr[i]]++;
    }
    int sorted[100000];
    // Change count[i] so that count[i] now contains actual
    // position of this character in output array
    for (int i = 1; i <= range; ++i)
        count[i] += count[i - 1];

    // Build the output character array
    for (int i = len-1; i>=0; i--) // running the loop forward will make it unstable
    {
        sorted[count[arr[i]] - 1] = arr[i];
        --count[arr[i]];
    }

    for (int i = 0; arr[i]; ++i)
        arr[i] = sorted[i];
}

int main()
{
    int arr[100000];

    int n;
    cin >> n;
    int i;
    for (i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    CountingSort(arr, i);
    for (i = 0; i < n; i++)
    {
        cout << arr[i]<<" ";
    }
    cout<<endl;
    return 0;
}