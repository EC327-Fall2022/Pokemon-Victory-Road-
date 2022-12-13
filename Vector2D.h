#ifndef Vector2D_H
#define Vector2D_H
#include <iostream>
#include <math.h>
#include <string>
using namespace std;

class Vector2D
{
    public:
    double x, y;
    Vector2D();
    Vector2D(double in_x, double in_y); 
};
ostream& operator<< (ostream&, const Vector2D&);
Vector2D operator* (const Vector2D&, double);
Vector2D operator/ (const Vector2D&, double);
#endif
