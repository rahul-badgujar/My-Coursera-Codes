#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>
#include <cfloat>
#define logn(x) cout << x << endl

typedef long long int Int;

using namespace std;

struct Point
{
    Int x, y;
    Point()
    {
        this->x = 0;
        this->y = 0;
    }
    Point(Int x, Int y)
    {
        this->x = x;
        this->y = y;
    }
};

double distance(Point a, Point b)
{
    double d = sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    return d;
}

bool compareX(Point a, Point b)
{
    return a.x < b.x;
}
bool compareY(Point a, Point b)
{
    return a.y < b.y;
}
double min(double a, double b)
{
    return a < b ? a : b;
}
double bruteDist(Point P[], Int n)
{
    double mn = DBL_MAX;
    for (Int i = 0; i < n; i++)
    {
        for (Int j = i + 1; j < n; j++)
        {
            double d = distance(P[i], P[j]);
            mn = min(mn, d);
        }
    }
    return mn;
}

double stripClosest(Point P[], Int n, double d)
{
    double mn=d;
    for (Int i = 0; i < n; i++)
    {
        for (Int j = i + 1; j < n && abs(P[j].y - P[i].y) < d; j++)
        {
            double t = distance(P[i], P[j]);
            mn = min(mn, t);
        }
    }
    return mn;
}

double closestDist(Point Px[], Point Py[], Int n)
{
    if (n <= 3)
    {
        return bruteDist(Px, n);
    }
    Int mid = n / 2;
    Point midPoint = Px[mid];
    Point Py1[mid], Py2[n - mid];
    Int l = 0, r = 0;
    for (Int i = 0; i < n; i++)
    {
        if (Py[i].x <= midPoint.x && l < mid)
        {
            Py1[l++] = Py[i];
        }
        else
            Py2[r++] = Py[i];
    }
    double ld = closestDist(Px, Py1, mid);
    double rd = closestDist(Px + mid, Py2, n - mid);
    double d = min(ld, rd);
    Point strip[n];
    Int j = 0;
    for (Int i = 0; i < n; i++)
    {
        if (abs(Py[i].x - midPoint.x) < d)
            strip[j++] = Py[i];
    }
    return stripClosest(strip, j, d);
}

int main()
{
    Int n;
    cin >> n;
    Point Px[n], Py[n];
    for (Int i = 0; i < n; i++)
    {
        Int x, y;
        cin >> x >> y;
        Px[i] = Py[i] = Point(x, y);
    }
    sort(Px, Px + n, compareX);
    sort(Py, Py + n, compareY);
    logn((double)closestDist(Px, Py, n));
}