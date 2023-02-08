#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

double expanding_rods(double L, double temp, double C)
{
    double _L = (1 + temp * C) * L, height;
    double lo = 0, hi = 1e9;
    while (lo < hi)
    {
        double mid = lo + (hi - lo) / 2; // mid = radius
        double angle = (_L/mid)/2;
        double maybe_L = 2*mid*sin(angle);
        if(fabs(maybe_L-L)<10e-6)
        {
            height = mid - mid*cos(angle);
            return height;
        }
        else if(maybe_L<L)
            lo = mid;
        else if(maybe_L>L)
            hi = mid;
    }
    return height;
}

int main()
{
    double t;
    cin >> t;
    int i = 1;
    while (t--)
    {
        double L, temp, C;
        cin >> L >> temp >> C;
        cout << "Case " << i++ << ": " << expanding_rods(L, temp, C)<<endl;
    }
    return 0;
}