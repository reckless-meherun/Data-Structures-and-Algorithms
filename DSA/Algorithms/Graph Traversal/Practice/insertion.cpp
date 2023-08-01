#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int insertion_sort(vector<int> num, int len)
{
    int count=0;
    for (int i = 1; i < len; i++)
    {
        int curr = num[i];
        int j=i-1;
        while(j>=0 and num[j]>curr)
        {
            num[j+1] = num[j];
            count++;
        }
        num[j+1] = curr;
    }    
    return count;
}

int main()
{
    int n;
    while(scanf("%d", &n)!=EOF)
    {
        vector<int> num;
        int i=0;
        while(n--)
        {
            int x;
            cin>>x;
            num.push_back(x);
            i++;
        }
        cout<<"Minimum exchange operations : "<<insertion_sort(num, i)<<endl;
    }
    return 0;
}