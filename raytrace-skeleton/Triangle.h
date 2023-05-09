#pragma once

#include "math3d.h"

class Triangle{
public:
    vec3 p[3];      //vertices
    vec3 e[3];      //edges: e[i] = p[i+1]-p[i]
    vec3 N;         //normal, unit length
    float D;	        //plane equation D
    float oneOverTwiceArea;	//1.0 / twice the triangle's area
    
    Triangle(vec3 a, vec3 b, vec3 c){
        p[0]=a;
        p[1]=b;
        p[2]=c;
        for(int i=0;i<3;++i)
            e[i] = p[(i+1)%3]-p[i];
        N = -1.0*cross(e[1],e[0]);
        float Nlen = length(N);
        oneOverTwiceArea = 1.0/Nlen;
        N = N * oneOverTwiceArea;
        D = -dot(N,p[0]);
    }
};
