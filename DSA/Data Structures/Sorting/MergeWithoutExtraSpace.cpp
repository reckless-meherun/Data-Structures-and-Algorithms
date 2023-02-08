#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void merge(int a1[], int a2[], int n, int m)
{
    int gap = (n+m+2-1)/2;

    while(gap>=1)
    {
        int i=0,j=i+gap;


        while(i<n && j<m+n)
        {
            if(j<n)
            {
                if(a1[i]>a1[j]) swap(a1[i],a1[j]);
            }
            if(j>=n)
            {
                int t = j-n;
                if(a1[i]>a2[t]) swap(a1[i],a2[t]);

            }
            i++;j++;
        }

        int temp = gap;
        gap = (gap+2-1)/2;
        if(temp==gap==1) break;
	}
}


int main()
{
    int T;
    cin >> T;

    while (T--)
    {
        int n, m;
        cin >> n >> m;

        int arr1[n], arr2[m];

        for (int i = 0; i < n; i++)
        {
            cin >> arr1[i];
        }

        for (int i = 0; i < m; i++)
        {
            cin >> arr2[i];
        }       
		merge(arr1, arr2, n, m);
		
        for (int i = 0; i < n; i++)
            cout << arr1[i] << " ";

        for (int i = 0; i < m; i++)
            cout << arr2[i] << " ";

        cout << endl;
    }

    return 0;
}