#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll m = 1e8 + 9;

ll binPow(ll a, ll b)
{
    if (b == 0)
        return 1;
    ll res = binPow(a, b / 2);
    if (b & 1)
        return (a * ((res % m) * (res % m)) % m) % m;
    else
        return ((res % m) * (res % m)) % m;
}

int main()
{
    ll m, n;
    cin>>m>>n;
    cout << binPow(m, n);
    return 0;
}