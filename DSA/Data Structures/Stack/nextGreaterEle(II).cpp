#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> nextGreaterElements(vector<int> &nums)
{
    int n = nums.size();
    vector<int> ans;
    stack<int> s;
    for (int i = 2 * n - 1; i >= 0; i--)
    {
        while (s.empty() == false && s.top() <= nums[i % n])
            s.pop();
        if (i < n)
        {
            int NGE = s.empty() ? -1 : s.top();
            ans.push_back(NGE);
        }
        s.push(nums[i % n]);
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

int main()
{
    freopen("input.in", "r", stdin);
    freopen("output.in", "w", stdout);
    int n;
    cin>>n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++)
    {
        cin>>nums[i];
    }

    vector<int> ans = nextGreaterElements(nums);
    for (auto v: ans)
    {
        cout<<v<<" ";
    }
    cout<<endl;    
    return 0;
}