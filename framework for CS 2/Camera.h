#pragma once 

#include "math3d.h"
#include "Program.h"

class Camera{
    public:
    float aspectRatio = 1.0f;
    vec3 eye;
    mat4 viewMatrix;
    mat4 projMatrix;
    float hither = 0.1f;
    float yon = 100.0f;
    float fov_v;
    float fov_h;
    vec3 right, up, look;
    
    Camera(vec3 eye, vec3 coi, vec3 up, float fov_v=30, float aspectRatio = 1.0f ){
        this->lookAt(eye,coi,up);
        this->fov_v = radians(fov_v);
        this->fov_h = aspectRatio * this->fov_v;
        this->aspectRatio = aspectRatio;
        this->updateProjMatrix();
    }
        
    void lookAt(vec3 eye, vec3 coi, vec3 up, float fov_v=0.0){
        if( fov_v != 0.0 ){
            this->fov_v = fov_v;
            this->fov_h = aspectRatio * fov_v;
            updateProjMatrix();
        }
        this->eye = eye;
        this->look = normalize(coi-this->eye);
        this->right = normalize(cross(this->look,up));
        this->up = cross( this->right, this->look );
        this->updateViewMatrix();
    }
        
    void updateViewMatrix(){
        this->viewMatrix = mat4(
            this->right.x, this->up.x, -this->look.x, 0,
            this->right.y, this->up.y, -this->look.y, 0,
            this->right.z, this->up.z, -this->look.z, 0,
            -dot(this->eye,this->right), -dot(this->eye,this->up), dot(this->eye,this->look), 1.0f);
    }
    
    void updateProjMatrix(){
        float P = 1 + (2*this->yon)/(this->hither-this->yon);
        float Q = 2 * this->hither * this->yon / (this->hither - this->yon );
        this->projMatrix = mat4(
            1/tan(this->fov_h),         0,                      0,      0,
            0,                              1/tan(this->fov_v), 0,      0,
            0,                              0,                      P,      -1,
            0,                              0,                      Q,       0
        );
    }
        
    void setUniforms(){
        Program::setUniform("viewMatrix", this->viewMatrix);
        Program::setUniform("projMatrix", this->projMatrix);
        Program::setUniform("eyePos", this->eye);
        Program::setUniform("cameraRight", this->right);
        Program::setUniform("cameraUp",this->up);
        Program::setUniform("cameraLook",this->look);
    }

    void turn( float amt ){
        auto M = axisRotation( this->up, amt );
        this->look = (vec4(this->look,0)*M).xyz();
        this->right = (vec4(this->right,0)*M).xyz();
        this->updateViewMatrix();
    }
 
    void tilt( float amt ){
        auto M = axisRotation( this->right, amt );
        this->look = (vec4(this->look,0)*M).xyz();
        this->up = (vec4(this->up,0)*M).xyz();
        this->updateViewMatrix();
    }

    void walk( float amt ){
        this->strafe(0,0,amt);
    }
    
    void strafe(float dr, float du, float dl){
        auto delta = dr * this->right + du * this->up + dl * this->look;
        this->eye = this->eye + delta;
        this->updateViewMatrix();
    }
};

        
