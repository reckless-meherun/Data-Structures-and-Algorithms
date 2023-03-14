#include <bits/stdc++.h>
using namespace std;

// be careful of int and double

void InsertionSort(vector<double> &v, int len)
{
    for (int outer = 1; outer < v.size(); outer++)
    {
        double toPlace = v[outer];
        int inner = outer - 1;
        while (inner >= 0 and (v[inner] - toPlace)>0.00001) // cannot write v[inner]>v[outer] as v[outer] gets changed after one shift in the inner loop
        {
            v[inner + 1] = v[inner];
            inner--;
        }
        v[inner + 1] = toPlace;
    }
}

// Function to sort arr[] of
// size n using bucket sort
void bucketSort(double arr[], int n)
{
    // 1) Create n empty buckets
    vector<double> b[n];

    // 2) Put array elements
    // in different buckets
    for (int i = 0; i < n; i++)
    {
        int bi = n * arr[i]; // Index in bucket
        b[bi].push_back(arr[i]);
    }

    // 3) Sort individual buckets
    for (int i = 0; i < n; i++)
        InsertionSort(b[i], b[i].size());
    
    // 4) Concatenate all buckets into arr[]
    int index = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < b[i].size(); j++)
            arr[index++] = b[i][j];
}

/* Driver program to test above function */
int main()
{
    freopen("input.in", "r", stdin);
    freopen("output.in", "w", stdout);
    double arr[] = {0.657, 0.565, 0.656, 0.1234, 0.655, 0.3434};
    int n = sizeof(arr) / sizeof(arr[0]);
    bucketSort(arr, n);

    cout << "Sorted array is \n";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    return 0;
}