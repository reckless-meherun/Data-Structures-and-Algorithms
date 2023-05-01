#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// 00101001

int numSubarraysWithSum(vector<int> &nums, int goal)
{
    int ans = 0, count = 0, sum = 0, i = 0;
    bool eql = false;
    if (goal != 0)
    {
        for (int j = 0; j < nums.size(); j++)
        {
            sum += nums[j];
            if (sum == goal)
            {
                while (sum == goal and i <= j)
                {
                    // cout<<i<<" "<<j<<" ans "<<ans<<" count "<<count<<endl;
                    ans++;
                    count++;
                    sum -= nums[i];
                    i++;
                }
            }
            else
            {
                if (nums[j] == 0)
                {
                    ans += count;
                    cout << i << " " << j << " ans " << ans << " count " << count << endl;
                }
                else
                    count = 0;
            }
        }
    }
    else
    {
        
    }
    return ans;
}

int main()
{
    // freopen("input.in", "r", stdin);
    // freopen("output.in", "w", stdout);
    int n, k;
    cin >> n >> k;
    vector<int> num(n);
    for (int i = 0; i < n; i++)
    {
        cin >> num[i];
    }
    numSubarraysWithSum(num, k);
    return 0;
}