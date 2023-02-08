#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int bin_search(int arr[], int n, int pivot, int find)
{
    int lo = 0, hi = pivot;
    int mid, ans;

    while (lo <= hi)
    {
        mid = lo + (hi - lo) / 2;
        if (arr[mid]<find)
        {
            lo = mid+1;
        }
        else if (arr[mid]>find)
        {
            hi = mid-1;
        }
        else
        {
            return mid;
        }
    }
    
    if(pivot!=n-1)
    	lo = pivot+1;
    else
    	lo=pivot;
    hi = n-1;
    while (lo <= hi)
    {
        mid = lo + (hi - lo) / 2;
        if (arr[mid]<find)
        {
            lo = mid+1;
        }
        else if (arr[mid]>find)
        {
            hi = mid-1;
        }
        else
        {
            return mid;
        }
    }
    return -1;
}

int find_pivot(int arr[], int len)
{
    int lo = 0, hi = len - 1;
    int mid, ans = 0;
    if (arr[lo] < arr[hi])
        return hi; // why not hi????

    while (lo <= hi)
    {
        mid = lo + (hi - lo) / 2;
        if (arr[mid] >= arr[lo])
        {
            ans = mid;
            lo = mid + 1;
        }
        else if (arr[mid] < arr[lo])
        {
            hi = mid - 1;
        }
    }
    return ans;
}

int main()
{
    int n, find;
    cin >> n;
    int arr[1000000];
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    cin >> find;
    int pivot = find_pivot(arr, n);
    //cout<<pivot<<endl;
    int pos = bin_search(arr, n, pivot, find);
    cout<<pos<<endl;
    return 0;
}