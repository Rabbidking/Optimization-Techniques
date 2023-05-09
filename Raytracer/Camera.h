#pragma once

#include "math3d.h"

class Camera{
public:
    vec3 right,up,look;
    vec3 eye;
    float fov_radians;
    Camera(){
        right=vec3(1,0,0);
        up=vec3(0,1,0);
        look=vec3(0,0,-1);
        eye = vec3(0,0,2);
        fov_radians = 45 / 180.0 * 3.14159265358979323;
    }
    void lookAt(vec3 eye, vec3 coi, vec3 up, float fov_degrees){
        fov_radians = fov_degrees / 180.0 * 3.14159265358979323;
        this->eye = eye;
        this->look = normalize(coi-eye);
        this->right = normalize(cross(look,up));
        this->up = cross( right, look );
    }

};
