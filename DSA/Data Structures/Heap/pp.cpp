#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int numSubarraysWithSum(vector<int> &nums, int goal)
{
    int sum = 0;
    int i = 0, j = 0;
    int count = 0;
    int res = 0;
    for (; j < nums.size(); j++)
    {
        sum += nums[j];
        while (sum > goal)
        {
            sum -= nums[i++];
        }
        while (sum == goal)
        {
            count++;
            sum -= nums[i++];
        }
    }
    return count;
}

int main()
{
    // freopen("input.in", "r", stdin);
    // freopen("output.in", "w", stdout);
    int n;
    int k;
    vector<int> num(n);
    cin >> n >> k;
    for (int i = 0; i < n; i++)
    {
        cin >> num[i];
    }

    cout << numSubarraysWithSum(num, k) << endl;

    return 0;
}

// 10 2
// 2 2 2 1 2 2 1 2 2 2