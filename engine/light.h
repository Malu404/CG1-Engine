#ifndef LIGHT_H
#define LIGHT_H

#include "../utils/vec3.h"

class Light {
    public:
        Vec3 pos;
        Vec3 color;
        double intensity;
        Light (): pos(Vec3()), color(Vec3(1.0, 1.0, 1.0)), intensity(1.0) {}
        Light (Vec3 pos, Vec3 color, double intensity): pos(pos), color(color), intensity(intensity) {}
};

#endif