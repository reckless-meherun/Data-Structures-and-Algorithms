#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void nextGreaterElements(vector<int> &nums)
{
    int len = nums.size();
    vector<int> ans(len);
    stack<pair<int, int>>s;
    bool flag=false;
    int j=0;
    for(int i=0; ; i++ )
    {
    	if(flag==false and i>=len)
    	{
    		i%=len;
    		len--;
    		flag=true;
    	}
    	
    	while(!s.empty() and nums[i]>s.top().first)
    	{
    		cout<<nums[i]<<" for "<<s.top().first<<" at "<<s.top().second<<endl;
    		ans[s.top().second] = nums[i];
    		s.pop();
    	}
        s.push({nums[i], i});
       // i++;
    	if(flag==true and i>=len)
        	break;
    }
    while(!s.empty())
    {
    	cout<<"-1 for "<<s.top().first<<" at "<<s.top().second<<endl;
        ans[s.top().second] = -1;
        s.pop();
    }
    for(int i=0; i<len+1; i++)
    {
        cout<<ans[i]<<" ";
    }
}

int main()
{
    
    int n;
    cin >> n;
    vector<int> s(n);
    for (int i = 0; i < n; i++)
    {
        cin >> s[i];
    }

   nextGreaterElements(s) ;
    return 0;
}