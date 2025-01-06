#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <stdexcept>
using namespace std;

double clip(double n, double lower, double upper) {
  return std::max(lower, std::min(n, upper));
}

struct Vec3 {
    double x, y, z;
    Vec3 ():  x(0), y(0), z(0) {};
    Vec3 (double x, double y, double z): x(x), y(y), z(z) {};
    
    inline Vec3 operator+(const Vec3& other) { return Vec3(x+other.x, y+other.y, z+other.z); }

    inline Vec3 operator-(const Vec3& other) { return Vec3(x-other.x, y-other.y, z-other.z); }

    inline Vec3 operator-() const { return Vec3(-x, -y, -z); }

    inline Vec3 operator*(const double other) const { return Vec3(x*other, y*other, z*other); }

    inline friend Vec3 operator*(double scalar, const Vec3& other) { return Vec3(other.x*scalar, other.y*scalar, other.z*scalar); }

    inline Vec3 operator*(const Vec3& other) const { return Vec3(x*other.x, y*other.y, z*other.z); }

    inline Vec3 operator/(const double other) const { return Vec3(x/other, y/other, z/other); }

    inline friend Vec3 operator/(double scalar, const Vec3& other) { return Vec3(other.x/scalar, other.y/scalar, other.z/scalar); }

    inline Vec3 operator/(const Vec3& other) const { return Vec3(x/other.x, y/other.y, z/other.z); }

    inline bool operator==(const Vec3& other) const { return (x == other.x) && (y == other.y) && (z == other.z); }

    inline double dot(const Vec3& other) const { return x*other.x + y*other.y + z*other.z; }

    inline double magnitude() const { return sqrt(x*x + y*y + z*z); }

    inline Vec3 normalize() const { return *this / magnitude(); }

    inline Vec3 rgb_normalized() const { return Vec3(x/255.0, y/255.0, z/255.0); }

    inline Vec3 rgb_255() const { return Vec3(x*255.0, y*255.0, z*255.0); }

    inline Vec3 clamp(double min, double max) { return Vec3(clip(x, min, max), clip(y, min, max), clip(z, min, max)); }

    inline friend std::ostream& operator<<(std::ostream& os, const Vec3& vec) {
        os << "Vec3(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
        return os;
    }
};

#endif