#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <ostream>

struct Vector {
    double x, y, z;

    explicit Vector(double x = 0.0, double y = 0.0, double z = 0.0);
    Vector& operator +=(const Vector &v);
    Vector& operator -=(const Vector &v);
    Vector& operator *=(double a);
};

Vector operator -(const Vector &v);
Vector operator +(const Vector &v, const Vector &u);
Vector operator -(const Vector &v, const Vector &u);
double operator *(const Vector &v, const Vector &u);
Vector operator *(double a, const Vector &v);
Vector operator *(const Vector &v, double a);

double abs(const Vector &v);

std::ostream& operator <<(std::ostream &out, const Vector &v);

#endif
