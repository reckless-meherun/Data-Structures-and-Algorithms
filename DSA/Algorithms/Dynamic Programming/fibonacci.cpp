#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll fibo[100000], vi[100000];

ll fibonacci(ll n)
{
    if (n < 2)
        return n;
    if (vi[n])
        return fibo[n];
    fibo[n] = fibonacci(n - 1) + fibonacci(n - 2);
    vi[n] = 1;
    return fibo[n];
}

int main()
{
    memset(vi, 0, sizeof(vi));
    ll x;
    cin >> x;
    cout << fibonacci(x);
    return 0;
}