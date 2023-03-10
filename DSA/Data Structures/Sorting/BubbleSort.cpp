#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void bubbleSort(vector<int> &v, int len)
{
    bool swapped = false;
    for (int outer = 0; outer < len - 1; outer++) // or outer = len-1; outer>0; outer--
    {
        swapped = false;
        for (int inner = 0; inner < len - 1 - outer; inner++) // or inner = 0; inner < outer; inner++
        {
            if (v[inner] > v[inner + 1]) // "<"" makes u set the smallest element first
            {
                swap(v[inner], v[inner + 1]);
                swapped = true;
            }
        }
        if (!swapped)
        {
            break; // the array is sorted
        }
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

    bubbleSort(v, n);
    for (int i = 0; i < n; i++)
    {
        cout << v[i] << " ";
    }
    return 0;
}