#include <bits/stdc++.h>
using namespace std;

int findPeak(int arr[], int n)
{
    int lo = 0;
    int hi = n - 1;
    int mid;

    if(n==1)
        return arr[0];

    while (lo <= hi)
    {
        mid = lo + (hi - lo) / 2;

        if (mid == 0)
        {
            if (arr[mid] < arr[mid + 1])
                lo = mid + 1;
            else
                return arr[mid];
        }
        else if (mid == n - 1)
        {
            if (arr[mid] < arr[mid - 1])
                hi = mid - 1;
            else
                return arr[mid];
        }
        else
        {
            if (arr[mid] > arr[mid - 1] and arr[mid] < arr[mid + 1])
            {
                lo = mid + 1;
            }
            else if (arr[mid] < arr[mid - 1] and arr[mid] > arr[mid + 1])
            {
                hi = mid - 1;
            }
            else
            {
                return arr[mid];
            }
        }
    }
    return -1;
}

int main()
{
    freopen("input.in", "r", stdin);
    freopen("output.in", "w", stdout);
    
    int arr[] = {1, 3, 5, 6, 9, 11, 7, 4, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    cout << "Value of the peak point is " << findPeak(arr, n);
    return 0;
}
