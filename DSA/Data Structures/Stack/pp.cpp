#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int findLengthOfShortestSubarray(vector<int> &arr)
{
    stack<int> s;
    int count = 0;
    for (int i = 0; i < arr.size(); i++)
    {
        if (!s.empty() and s.top() > arr[i])
        {
            s.pop();
            count++;
            s.push(arr[i]);
        }
        else
        {
            s.push(arr[i]);
        }
    }
    return count;
}

int main()
{
    // freopen("input.in", "r", stdin);
    // freopen("output.in", "w", stdout);
    vector<int> arr;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        arr.push_back(x);
    }

    cout << findLengthOfShortestSubarray(arr);

    return 0;
}