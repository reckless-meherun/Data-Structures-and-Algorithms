#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int Josh(vector<int> person, int k, int index)
{
    if (person.size() == 1)
    {
        return person[0];
    }

    index = ((index + k) % person.size());
    person.erase(person.begin() + index);

    return Josh(person, k, index);
}

class Solution
{
public:
    int findTheWinner(int n, int k)
    {
        vector<int> ppl;
        for (int i = 1; i <= n; i++)
        {
            ppl.push_back(i);
        }
        int start = 0;
        k--;
        return Josh(ppl, k, start);
    }
};

int main()
{
    freopen("input.in", "r", stdin);
    freopen("output.in", "w", stdout);
    Solution sol;
    int n, k;
    cin >> n >> k;
    
	cout<<sol.findTheWinner(n, k)<<endl;
    return 0;
}
