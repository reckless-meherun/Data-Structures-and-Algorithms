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
    int n, m;
    cin >> n >> m;
    int mat[1000][1000];

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> mat[i][j];
        }
    }

    vector<int> sorted(10000);
    for (int k = 0; k < m; k++)
    {
        int s = 0;
        for (int i = 0, j = k; i < n and j < m;)
        {
            sorted[s++] = mat[i][j];
            i++;
            j++;
        }
        //sort(sorted.begin(), sorted.begin() + s);
        bubbleSort(sorted, s);
        s = 0;
        for (int i = 0, j = k; i < n and j < m;)
        {
            mat[i][j] = sorted[s++];
            i++;
            j++;
        }
    }

    for (int k = 0; k < n; k++)
    {
        int s = 0;
        for (int i = k, j = 0; i < n and j < m;)
        {
            sorted[s++] = mat[i][j];
            i++;
            j++;
        }
        bubbleSort(sorted, s);
        s = 0;
        for (int i = k, j = 0; i < n and j < m;)
        {
            mat[i][j] = sorted[s++];
            i++;
            j++;
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout<< mat[i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}