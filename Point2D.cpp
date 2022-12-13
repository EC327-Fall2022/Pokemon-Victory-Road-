#include <iostream>
#include <cmath>
#include "Point2D.h"
#include "Vector2D.h"
using namespace std;

Point2D::Point2D() 
{
    x = 0;
    y = 0;
}

Point2D::Point2D(double in_x, double in_y)
{
    x = in_x;
    y = in_y;
}

double GetDistanceBetween(Point2D p1, Point2D p2)
{
    double distance = 0;
    double a = p1.x - p2.x;
    double b = p1.y - p2.y;
    a = pow(a,2);
    b = pow(b,2);
    distance = a+b;
    distance = sqrt(distance);
    return distance;    
}

ostream& operator<< (ostream& out, const Point2D& p1)
{
    out << "(" << p1.x << ", " << p1.y << ")";
    return out;
}

Point2D operator+ (const Point2D&  p1, const Vector2D& v1)
{
    Point2D p2;
    p2.x = (p1.x + v1.x);
    p2.y = (p1.y + v1.y);
    return p2;
}

Vector2D operator- (const Point2D& p1, const Point2D& p2)
{
    Vector2D p3;
    p3.x = (p1.x - p2.x);
    p3.y = (p1.y - p2.y);
    return p3;
}