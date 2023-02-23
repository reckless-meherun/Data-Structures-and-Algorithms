#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<vector<int>> diagonalSort(vector<vector<int>> &mat)
{
    // vector<vector<int>>ans;
    int n = mat.size();
    int m = mat[0].size();

    // <!--sorting from first row to the last row-->

        for (int i = 0; i < n; i++)
    {
        int k = i;
        int j = 0;
        vector<int> v;
        while (k < n && j < m)
        {
            v.push_back(mat[k][j]);
            j++;
            k++;
        }
        sort(v.begin(), v.end());
        k = i;
        j = 0;
        int l = 0;
        while (k < n && j < m && l < v.size())
        {
            mat[k][j] = v[l];
            k++;
            j++;
            l++;
        }
    }
    // <!--sorting from 2nd column to last column-->

        for (int j = 1; j < m; j++)
    {
        int k = j;
        int i = 0;
        vector<int> v;
        while (k < m && i < n)
        {
            v.push_back(mat[i][k]);
            i++;
            k++;
        }
        sort(v.begin(), v.end());
        k = j;
        i = 0;
        int l = 0;
        while (k < m && i < n && l < v.size())
        {
            mat[i][k] = v[l];
            k++;
            i++;
            l++;
        }
    }
    return mat;
}

int main()
{
    freopen("input.in", "r", stdin);
    freopen("output.in", "w", stdout);
    return 0;
}