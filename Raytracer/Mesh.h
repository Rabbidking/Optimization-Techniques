#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <map>
#include <array>
#include <memory>
#include "Triangle.h"
#include "math3d.h"

class Mesh{
  public:    
    std::vector<Triangle> triangles;
    vec3 color;
    float alpha;
    float refl;
    
    /** Load OBJ file*/
    Mesh(std::string filename, float tx, float ty, float tz, float scale, vec3 color, float a, float refl){
        this->color = color;
        this->alpha=a;
        this->refl=refl;
        
        using namespace std;
        
        std::ifstream in(filename.c_str());
        if(!in.good() )
            throw std::runtime_error("Cannot open "+filename);
            
        std::vector<vec3> P;
        while(true){
            std::string line;
            std::getline(in,line);
            if(in.fail() )
                break;
            std::istringstream iss(line);
            std::string word;
            iss >> word;
            if( word == "v" ){
                float x,y,z;
                iss >> x >> y >> z;
                P.push_back(vec3(x*scale+tx,y*scale+ty,z*scale+tz));
            }
            else if( word == "f" ){
                std::vector< int > I;
                while(true){
                    iss >> word;
                    if( iss.fail() )
                        break;
                    istringstream Q(word);
                    int vi;
                    Q >> vi ;
                    if( Q.fail() )
                        break;
                    //doesn't support negative indices...
                    I.push_back(vi-1);
                }
                for(unsigned i=2;i<I.size();++i){
                    vec3 p0 = P[I[0]];
                    vec3 p1 = P[I[i-1]];
                    vec3 p2 = P[I[i]];
                    Triangle tr(p0,p1,p2);
                    this->triangles.push_back(tr);
                }
            }
        }
    }
};
