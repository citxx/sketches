#include "Vector.hpp"
#include <cmath>

Vector::Vector(double x, double y, double z): x(x), y(y), z(z) {
}

Vector& Vector::operator +=(const Vector &v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

Vector& Vector::operator -=(const Vector &v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

Vector& Vector::operator *=(double a) {
    x *= a;
    y *= a;
    z *= a;
    return *this;
}

Vector operator -(const Vector &v) {
    return Vector(-v.x, -v.y, -v.z);
}

Vector operator +(const Vector &v, const Vector &u) {
    return Vector(v.x + u.x, v.y + u.y, v.z + u.z);
}

Vector operator -(const Vector &v, const Vector &u) {
    return Vector(v.x - u.x, v.y - u.y, v.z - u.z);
}

double operator *(const Vector &v, const Vector &u) {
    return v.x*u.x + v.y*u.y + v.z*u.z;
}

Vector operator *(double a, const Vector &v) {
    return Vector(a*v.x, a*v.y, a*v.z);
}

Vector operator *(const Vector &v, double a) {
    return Vector(a*v.x, a*v.y, a*v.z);
}

double abs(const Vector &a) {
    return sqrt(a*a);
}

std::ostream& operator <<(std::ostream &out, const Vector &v) {
    out << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return out;
}
