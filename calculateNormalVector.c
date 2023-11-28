#include "CSCIx229.h"


Point subtract(Point a, Point b) {
    Point result = {a.x - b.x, a.y - b.y, a.z - b.z};
    return result;
}

Point cross_product(Point a, Point b) 
{
    Point result = {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
    return result;
}

double length(Point a) 
{
    return sqrt(a.x*a.x + a.y*a.y + a.z*a.z);
}

Point normalize(Point a)
 {
    double len = length(a);
    Point result = {a.x/len, a.y/len, a.z/len};
    return result;
}

Point calculate_normal(Point p0, Point p1, Point p3) 
{
    Point v1 = subtract(p1, p0);
    Point v2 = subtract(p3, p0);
    Point normal = cross_product(v1, v2);
    return normalize(normal);
}