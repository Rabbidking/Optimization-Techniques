#pragma once

#include "math3d.h"

class Sphere{
    public:
    vec3 c;     //center
    float r;    //radius
    vec3 color;
    float alpha;
    float refl;
    Sphere(vec3 c, float r, vec3 color, float a, float ref){
        this->c=c;
        this->r=r;
        this->color=color;
        alpha=a;
        refl=ref;
    }
};
    
