#include <bits/stdc++.h>
using namespace std;

/** be careful of int and double */

void InsertionSort(vector<double> &v, int len)
{
    for (int outer = 1; outer < v.size(); outer++)
    {
        double toPlace = v[outer];
        int inner = outer - 1;
        while (inner >= 0 and (v[inner] - toPlace) > 0.00001) // cannot write v[inner]>v[outer] as v[outer] gets changed after one shift in the inner loop
        {
            v[inner + 1] = v[inner];
            inner--;
        }
        v[inner + 1] = toPlace;
    }
}

double findMax(double arr[], int len)
{
    double Max = arr[0];
    for (int i = 0; i < len; i++)
    {
        if (arr[i] - Max > 0.00000001)
            Max = arr[i];
    }
    return Max;
}

double findMin(double arr[], int len)
{
    double Min = arr[0];
    for (int i = 0; i < len; i++)
    {
        if (arr[i] - Min < 0.00000001)
            Min = arr[i];
    }
    return Min;
}

void bucketSort(double arr[], int totalElem, int totalBuck)
{
    double MaxElem = findMax(arr, totalElem);
    double MinElem = findMin(arr, totalElem);

    double bucketRange = (MaxElem - MinElem) / totalBuck;
    vector<double> bucket[totalBuck];

    for (int i = 0; i < totalElem; i++)
    {
        double buckIndex = (arr[i] - MinElem) / bucketRange;
        double diference = buckIndex - (int)buckIndex;

        if (diference == 0 and arr[i] == MaxElem)
        {
            bucket[(int)buckIndex - 1].push_back(arr[i]);
            continue;
        }

        bucket[(int)buckIndex].push_back(arr[i]);
    }

    for (int i = 0; i < totalBuck; i++)
    {
        InsertionSort(bucket[i], bucket[i].size());
    }

    int k = 0;

    for (int i = 0; i < totalBuck; i++)
    {
        for (int j = 0; j < bucket[i].size(); j++)
        {
            arr[k++] = bucket[i][j];
        }
    }
}

int main()
{
    // freopen("input.in", "r", stdin);
    // freopen("output.in", "w", stdout);
    double arr[] = {1, 21, 0.656, 0.1234, 0.655, 0.3434};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 3;
    bucketSort(arr, n, k);

    cout << "Sorted array is \n";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    return 0;
}