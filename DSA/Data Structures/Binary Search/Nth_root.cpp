#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

double mul(double mid, double root)
{
    double x = 1;
    while (root--)
        x *= mid;

    return x;
}

void Nth_root(double num, double root)
{
    double mid, lo, hi;
    lo = 1;
    hi = num;

    for (ll i = 0; i < 100; i++)
    {
        mid = lo + (hi - lo) / 2;

        if (mul(mid, root) > num)
            hi = mid;
        else if (mul(mid, root) < num)
            lo = mid;
    }
    cout << setprecision(10) << lo << endl;
    return;
}

int main()
{
    double num;
    cin >> num;
    double root;
    cin >> root;
    Nth_root(num, root);
    return 0;
}