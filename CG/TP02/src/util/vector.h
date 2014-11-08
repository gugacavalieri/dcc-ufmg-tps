#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
#include <iostream>

class Vector
{
public:
    double x;
    double y;
    double z;

    Vector();
    Vector(double x,double y,double z);

    void Normalize();

    double Dot(const Vector &v) const;
    Vector Cross(const Vector &v)const;
    double AngleBetween(const Vector &v)const;

    void operator+=(const Vector& v);
    void operator-=(const Vector& v);

    Vector operator+(const Vector& v)const;
    Vector operator-(const Vector& v)const;

    Vector operator=(const Vector& v);

    void operator/=(const Vector& v);
    void operator/=(const double d);
    Vector operator/(const Vector& v)const;
    Vector operator/(const double d)const;

    double Length()const;
};

Vector vector_cross(const Vector &v1, const Vector &v2);
Vector multiply(Vector v, const double d);

#endif // VECTOR_H
