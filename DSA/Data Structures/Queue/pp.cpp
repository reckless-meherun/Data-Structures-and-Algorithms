#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int maxSubarraySumCircular(vector<int> &nums)
{
    ll max_sum = INT_MIN, min_sum = INT_MAX, curr1_sum = 0, curr2_sum = 0;

    ll total_sum = 0;

    for (int i = 0; i < nums.size(); i++)
    {
        total_sum += nums[i];

        curr1_sum += nums[i];
        if (curr1_sum > max_sum)
            max_sum = curr1_sum;
        if (curr1_sum < 0)
            curr1_sum = 0;

        curr2_sum += nums[i];
        if (curr2_sum < min_sum)
            min_sum = curr2_sum;
        if (curr2_sum > 0)
            curr2_sum = 0;
    }
    
    if (total_sum == min_sum)
        return max_sum;
    else
        return max(max_sum, total_sum - min_sum);
    // the maximum between the non-circular maximum sum and circular maximum sum
    // as there is no guarranty that the maximum sum of the circular one
    // is larger than the non-circular one
}

int main()
{
    freopen("input.in", "r", stdin);
    freopen("output.in", "w", stdout);

    ll n;
    cin >> n;
    vector<int> nums(n);
    for (ll i = 0; i < n; i++)
    {
        cin >> nums[i];
    }
    maxSubarraySumCircular(nums);
    return 0;
}