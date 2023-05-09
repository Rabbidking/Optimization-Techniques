#pragma once

#include <string>
#include "Sphere.h"
#include "Mesh.h"
#include <vector>
#include <fstream>
#include <sstream>

class Scene {
    public:
    std::vector<Sphere> spheres;
    std::vector<Mesh> meshes;
    Camera camera;
    vec3 lightPosition = vec3(0,10,0);
    
    Scene(std::string filename){
        int numtris=0;
        std::ifstream in(filename);
        if(!in.good() )
            throw new std::runtime_error("Cannot open scene file "+filename);
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
                float r,g,b,a,refl;
                iss >> r >> g >> b >> a >> refl >> x >> y >> z >> rad;
                spheres.push_back(Sphere(vec3(x,y,z),rad,vec3(r,g,b),a,refl));
            } else if(word == "mesh" ){
                float r,g,b,a,refl;
                std::string fname;
                iss >> r >> g >> b >> a >> refl;
                float tx,ty,tz;
                iss >> tx >> ty >> tz;
                float sc;
                iss >> sc;
                getline(iss,fname);
                while(fname.length() > 0 && fname[0] == ' ')
                    fname = fname.substr(1);
                meshes.push_back(Mesh(fname,tx,ty,tz,sc,vec3(r,g,b),a,refl));
                numtris += meshes.back().triangles.size();
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
                iss >> lightPosition.x >> lightPosition.y >> lightPosition.z;
            } else {
                throw std::runtime_error("Bad line: "+line);
            }
        }
        std::cout << spheres.size() << " spheres\n";
        std::cout << numtris << " triangles\n";
    }
};

