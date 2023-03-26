#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main()
{
    freopen("input.in", "r", stdin);
    freopen("output.in", "w", stdout);
    queue<int> q1;
    queue<int> q2;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        q1.push(x);
    }
    int target_sum;
    cin >> target_sum;
    int sum = 0;
    bool found = false;

    while (!q1.empty())
    {
        if (sum == target_sum)
        {
            found = true;
            break;
        }
        else if (sum < target_sum)
        {
            sum += q1.front();
            q2.push(q1.front());
            q1.pop();
        }
        else
        {
            // break;
            while (!q2.empty() and (sum - q2.front()) > target_sum)
            {
                sum -= q2.front();
                q2.pop();
            }
            if (!q2.empty() and sum > target_sum)
            {
                sum -= q2.front();
                q2.pop();
            }
            if (sum == target_sum)
            {
                found = true;
                break;
            }
        }
        
    }

    if(found)
    {
        while(!q2.empty())
        {
            cout<<q2.front()<<" ";
            q2.pop();
        }
    }
    else
        cout<<"Not found"<<endl;
    return 0;
}