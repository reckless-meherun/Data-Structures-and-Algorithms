#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int findMin(vector<int> &nums)
{

    return findMin(nums, 0, nums.size() - 1);
}

bool alreadySorted(vector<int> &nums, int l, int r) 
{ 
    return nums[l] < nums[r]; 
}

int findMin(vector<int> &nums, int l, int r)
{
    if (l == r || alreadySorted(nums, l, r))
        return nums[l];
    int m = l + (r - l) / 2;
    int left = findMin(nums, l, m);
    int right = findMin(nums, m + 1, r);
    return min(left, right);
}

int main()
{
    freopen("input.in", "r", stdin);
    freopen("output.in", "w", stdout);
    
    return 0;
}