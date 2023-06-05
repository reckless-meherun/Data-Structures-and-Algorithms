#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void SelectionSort(vector<int> &v, int len)
{
    for (int outer = 0; outer < len - 1; outer++) // or outer = len-1; outer>0; outer--
    {
        for (int inner = outer + 1; inner < len; inner++) // or inner = 0; inner < outer; inner++
        {
            if (v[outer] > v[inner]) // "<"" makes u set the smallest element first
            {
                swap(v[outer], v[inner]);
            }
        }
    }
}

void SelectionSort_WithmidIndex(vector<int> &v, int len)
{
    for (int outer = 0; outer < len - 1; outer++) // or outer = len-1; outer>0; outer--
    {
        int min_index = outer;
        for (int inner = outer + 1; inner < len; inner++) // or inner = 0; inner < outer; inner++
        {
            if (v[min_index] > v[inner]) // "<"" makes u set the smallest element first
            {
                min_index = inner;
            }
        }
        swap(v[min_index], v[outer]);
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

    SelectionSort_WithmidIndex(v, n);
    for (int i = 0; i < n; i++)
    {
        cout << v[i] << " ";
    }    
    return 0;
}