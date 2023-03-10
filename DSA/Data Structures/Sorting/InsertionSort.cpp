#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void InsertionSort(vector<int> &v, int len)
{
    for (int outer = 1; outer < len; outer++) 
    {
        int toPlace = v[outer]; // u have to save it as before shifting
        int inner = outer - 1;
        while(inner>=0 and v[inner]>toPlace) // cannot write v[inner]>v[outer] as v[outer] gets changed after one shift in the inner loop
        {
            v[inner+1] = v[inner];
            inner--;
        }
        v[inner+1] = toPlace; 
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

    InsertionSort(v, n);
    for (int i = 0; i < n; i++)
    {
        cout << v[i] << " ";
    }

    return 0;
}