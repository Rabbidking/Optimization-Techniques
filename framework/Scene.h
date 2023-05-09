#pragma once

#include <string>
#include "Sphere.h"
#include "Mesh.h"
#include "utils.h"
#include <vector>
#include <fstream>
#include <sstream>

class Scene {
    public:
    std::vector<Sphere> spheres;
    std::vector<Mesh> meshes;
    Camera camera{vec3(0,0,3), vec3(0,0,0), vec3(0,1,0) };
    vec3 lightPosition;
    
    Scene(std::string filename){
        std::ifstream in(filename);
        if(!in.good() )
            throw std::runtime_error("Cannot open scene file "+filename);
        while(true){
            std::string line;
            getline(in,line);
            if( in.fail() )
                break;
            std::istringstream iss(line);
            std::string word;
            iss >> word;
            if(word.length() == 0 ){
            } else if( word[0] == '#' ){
                //comment
            } else if( word == "sphere" ){
                float x,y,z;
                float rad;
                float r,g,b,a,R;
                iss >> r >> g >> b >>a >> R >> x >> y >> z >> rad;
                spheres.push_back(Sphere(vec3(x,y,z),rad,vec3(r,g,b),a,R));
            } else if(word == "mesh" ){
                float r,g,b,a,R;
                std::string fname;
                iss >> r >> g >> b >> a >> R;
                float tx,ty,tz;
                iss >> tx >> ty >> tz;
                float sc;
                iss >> sc;
                getline(iss,fname);
                while(fname.length() > 0 && fname[0] == ' ')
                    fname = fname.substr(1);
                meshes.push_back(Mesh(fname,tx,ty,tz,sc,vec3(r,g,b),a,R));
            } else if( word == "camera" ){
                vec3 eye;
                vec3 coi;
                vec3 up;
                float fov_degrees;
                iss >> eye.x >> eye.y >> eye.z;
                iss >> coi.x >> coi.y >> coi.z;
                iss >> up.x >> up.y >> up.z;
                iss >> fov_degrees;
                camera.lookAt(eye,coi,up,fov_degrees);
            } else if( word == "light" ){
                float x,y,z;
                iss >> x >> y >> z;
                lightPosition = vec3(x,y,z);
            } else {
                throw std::runtime_error("Bad line: "+line);
            }
        }
    }
};

