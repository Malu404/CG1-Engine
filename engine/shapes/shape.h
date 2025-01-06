#ifndef SHAPE_H
#define SHAPE_H

#include <tuple>
#include "material.h"
#include "../ray.h"

class Shape {
    public:
        Material mat;
        Shape () : mat(Material()) {}
        Shape (Material mat) : mat(mat) {}
        
        virtual Vec3 get_normal(Vec3 p) = 0;
        virtual std::tuple<bool, double, double> intersects(Ray r) = 0;
};

#endif