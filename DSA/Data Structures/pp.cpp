#include <bits/stdc++.h>
using namespace std;

long long N, Cow;
long long stall_pos[1000000];

bool possible(long long mid)
{
    long long last=-1;
    long long count = Cow;
    for (long long i = 0; i < N; i++)
    {
        if(stall_pos[i] - last>=mid or last==-1)
        {
            count--;
            last = stall_pos[i];           
        } 
        if(count==0)
            break;    
    }  
    return count==0;  
}

int main()
{
    long long t;
    cin >> t;
    
    while (t--)
    {        
        cin >> N >> Cow;
        for (long long i = 0; i < N; i++)
        {
            cin >> stall_pos[i];
        }
        sort(stall_pos, stall_pos + N);
        long long hi = 1e9, lo = 0, mid, ans;
        while (hi-lo>1)
        {
            mid = lo + (hi - lo) / 2;
            if (possible(mid))
            {
                lo=mid;
            }
            else
            {
                hi = mid - 1;
            }
        }
        if(possible(hi))
            cout<<hi<<endl;
        else
            cout<<lo;
    }
    return 0;
}