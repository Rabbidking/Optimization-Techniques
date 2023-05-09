#pragma once

#include "math3d.h"

class Sphere{
    public:
    vec3 c;     //center
    float r;    //radius
    float r2;
    vec3 color;
    float alpha;
    float refl;
    
    Sphere(vec3 c, float r, vec3 color, float a, float R){
        this->alpha =a ;
        this->refl = R;
        this->c=c;
        this->r=r;
        this->r2=r*r;
        this->color=color;
    }
};
    
