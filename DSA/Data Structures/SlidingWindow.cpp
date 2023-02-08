#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// to calculate the number of subarrays which elements' sum is equal to the required sum
int sliding_window(int arr[], int len, int sum)
{
    int curr_sum = arr[0], count = 0;
    for (int i = 0, j = 0; i < len;)
    {
       if(curr_sum>=sum)
       {
            if(curr_sum==sum)
                count++;
            curr_sum -= arr[i];
            i++;
       }
       else
       {
            while(curr_sum<sum)
            {
                j++;
                curr_sum += arr[j];
            }
       }
    }
    return count;
}

int main()
{
    int n, sum;
    cin >> n >> sum;
    int arr[2000000];
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    cout<<sliding_window(arr, n, sum)<<endl;

    return 0;
}