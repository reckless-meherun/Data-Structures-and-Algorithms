#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class point
{
public:
    int x, y;
};

vector<point> points;

bool compareX(point a, point b)
{
    return a.x < b.x;
}

bool compareY(point a, point b)
{
    return a.y < b.y;
}

int distance(point a, point b)
{
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

pair<point, point> closestThree(point a, point b, point c)
{
    int d1 = distance(a, b);
    int d2 = distance(b, c);
    int d3 = distance(c, a);

    int minD = min({d1, d2, d3});

    if (minD == d1)
        return {a, b};
    if (minD == d2)
        return {b, c};
    return {c, a};
}

void printStuff(pair<point, point> p1, pair<point, point> p2, int d1, int d2)
{
    cout << p1.first.x << " " << p1.first.y << endl;
    cout << p2.second.x << " " << p2.second.y << endl;

    cout << d1 << " " << d2 << endl;
}

pair<point, point> closestPair(int start, int end)
{
    if (start == end - 1)
        return {points[start], points[end]};
    if (start == end - 2)
        return closestThree(points[end], points[end - 1], points[end - 2]);

    int mid = (start + end) / 2;

    pair<point, point> p1 = closestPair(start, mid);
    pair<point, point> p2 = closestPair(mid + 1, end);

    int d1 = distance(p1.first, p1.second);

    int d2 = distance(p2.first, p2.second);
    // printStuff(p1, p2, d1, d2);

    int d = min(d1, d2);

    vector<point> strip;

    for (int i = start; i <= end; i++)
    {
        if (abs(distance(points[i], points[mid])) < d)
            strip.push_back(points[i]);
    }
    sort(strip.begin(), strip.end(), compareY);

    int len = strip.size();
    pair<point, point> retPoint;
    if (d == d1)
        retPoint = p1;
    else
        retPoint = p2;

    for (int i = 0; i < len; i++)
    {
        for (int j = i + 1; j < len and j <= i + 7; j++)
        {
            int dis = distance(points[i], points[j]);
            if (dis < d)
            {
                retPoint = {points[i], points[j]};
                d = dis;
            }
        }
    }
    strip.clear();
    return retPoint;
}

void findClosestDistance(int n)
{
    sort(points.begin(), points.end(), compareX);
    pair<point, point> closePoints = closestPair(0, n - 1);

    point p1 = closePoints.first;
    point p2 = closePoints.second;
    cout << setprecision(5) << sqrt(distance(p1, p2)) << "\n";
    cout << p1.x << " " << p1.y << endl;
    cout << p2.x << " " << p2.y << endl;
}

int main()
{
    int n;
    cin >> n;
    points.resize(n);
    for (int i = 0; i < n; i++)
    {
        cin >> points[i].x >> points[i].y;
    }
    findClosestDistance(n);
    return 0;
}