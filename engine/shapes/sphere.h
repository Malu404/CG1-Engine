#ifndef SPHERE_H
#define SPHERE_H

#include "shape.h"

class Sphere : public Shape {
    public:
        Vec3 center;
        double radius;
        Sphere (): center(Vec3(0.0, 0.0, 0.0)), radius(1.0), Shape() {}
        Sphere (Vec3 center, double radius, Material mat): center(center), radius(radius), Shape(mat) {}
        
        inline Vec3 get_normal(Vec3 p) override { return ( p - center ).normalize(); }
        
        tuple<bool, double, double> intersects(Ray r) override {
            Vec3 v = center - r.origin;
            double a = r.dr.dot(r.dr);
            double b = -2.0 * (r.dr.dot(v));
            double c = v.dot(v) - radius*radius;
            double delta = b*b - 4*a*c;

            if (delta > 0.0) {
                return make_tuple(true, (-b + sqrt(delta)) / (2.0*a), (-b - sqrt(delta)) / (2.0*a));
            } else {
                return make_tuple(false, -1.0, -1.0);
            }
        }
};

#endif