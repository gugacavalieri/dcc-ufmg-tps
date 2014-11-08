#include "../util/vector.h"

#include <cmath>

Vector::Vector()
{
    this->x=this->y=this->z=0;
}

Vector::Vector(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

void Vector::Normalize()
{
    double len = sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
    this->x /= len;
    this->y /= len;
    this->z /= len;
}

double Vector::Dot(const Vector & v)const
{
  return this->x * v.x + this->y * v.y + this->z * v.z;
}

Vector Vector::Cross(const Vector& v)const
{
    return Vector(this->y * v.z - this->z *v.y, this->z * v.x - this->x * v.z, this->x * v.y - this->y * v.x);
}

double Vector::AngleBetween(const Vector &v)const
{
    Vector v1 = v;
    Vector v2 = *this;
    v1.Normalize();
    v2.Normalize();
  if((v1.x == v2.x) && (v1.y == v2.y) && (v1.z == v2.z))
  {
    return 0;
  }
  else
  {
    return acos(v1.Dot(v2));
  }
}

void Vector::operator+=(const Vector& v)
{
  this->x += v.x;
  this->y += v.y;
  this->z += v.z;
}

void Vector::operator-=(const Vector& v)
{
  this->x -= v.x;
  this->y -= v.y;
  this->z -= v.z;
}

Vector Vector::operator+(const Vector& v)const
{
  return Vector(this->x + v.x, this->y + v.y ,this->z + v.z);
}

Vector Vector::operator-(const Vector& v)const
{
  return Vector(this->x - v.x, this->y - v.y, this->z - v.z);
}


void Vector::operator/=(const Vector& v)
{
  this->x /= v.x;
  this->y /= v.y;
  this->z /= v.z;
}

void Vector::operator/=(const double d)
{
  this->x /= d;
  this->y /= d;
  this->z /= d;
}

Vector Vector::operator/(const Vector& v)const
{
  return Vector(this->x / v.x, this->y / v.y, this->z / v.z);
}

Vector Vector::operator/(const double d)const
{
  return Vector(this->x / d, this->y / d, this->z / d);
}

Vector vector_cross(const Vector& v1, const Vector& v2) {
	return Vector(v1.y * v2.z - v1.z *v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
}

double Vector::Length()const
{
  return sqrt((this->x*this->x)+(this->y*this->y)+(this->z*this->z));
}

Vector Vector::operator=(const Vector& v)
{
  this->x = v.x;
  this->y = v.y;
  this->z = v.z;
  return *this;
}
